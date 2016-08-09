#include <petscviewerhdf5.h>
#include <stdexcept>

#include <mpi.h>
#include <fstream>
#include <Mesh/Mesh.h>
#include <Model/ExodusModel.h>
#include <Utilities/Options.h>
#include <Utilities/Utilities.h>
#include <Utilities/Logging.h>
#include <petscdmplex.h>
#include <Utilities/Types.h>

extern "C" {
#include <exodusII.h>
}

using std::unique_ptr;

Mesh::Mesh(const std::unique_ptr<Options> &options) {
  mExodusFileName = options->MeshFile();
  mDistributedMesh = NULL;
  mMeshSection = NULL;
  mNumDim = 0;
}

std::unique_ptr<Mesh> Mesh::Factory(const std::unique_ptr<Options> &options) {
  return std::unique_ptr<Mesh> (new Mesh(options));
}

void Mesh::read(int dim, int numCells, int numVerts, int numVertsPerElem,
                Eigen::MatrixXi cells, Eigen::MatrixXd vertex_coords) {

    // Class variables.
    mDistributedMesh = NULL;
    DM dm = NULL;
    PetscBool interpolate_edges = PETSC_TRUE;
    
    printf("cells=[");
    for(int i=0;i<numCells*numVertsPerElem;i++) {
      printf("%d, ",cells.data()[i]);
    }printf("]\n");
    DMPlexCreateFromCellList(PETSC_COMM_WORLD, dim, numCells, numVerts, numVertsPerElem,
                             interpolate_edges, cells.data(), dim, vertex_coords.data(),&dm);
    
    // May be a race condition on distribute.
    MPI::COMM_WORLD.Barrier();
    DMPlexDistribute(dm, 0, NULL, &mDistributedMesh);

  // We don't need the serial mesh anymore.
  if (mDistributedMesh) { DMDestroy(&dm); }
    // mDistributedMesh == NULL when only 1 proc is used.
  else { mDistributedMesh = dm; }

  DMGetDimension(mDistributedMesh, &mNumDim);
  DMPlexGetDepthStratum(mDistributedMesh, mNumDim, NULL, &mNumberElementsLocal);
}

void Mesh::read() {

  // Class variables.
  mDistributedMesh = NULL;

  // check if file exists
  PetscInt rank; MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
  if (rank == 0) {
    std::ifstream f(mExodusFileName.c_str());
    if (!f.good()) {
      throw std::runtime_error("Mesh file not found! You requested '" + mExodusFileName + "'.");
    }
  }
  MPI_Barrier(PETSC_COMM_WORLD);

  // Function variables.
  DM dm = NULL;
  PetscBool interpolate_edges = PETSC_TRUE;

  /* Read exodus file. */
  DMPlexCreateExodusFromFile(PETSC_COMM_WORLD, mExodusFileName.c_str(), interpolate_edges, &dm);

  /* Distribute mesh. */
  DMPlexDistribute(dm, 0, NULL, &mDistributedMesh);

  /* We don't need the serial mesh anymore if we're in parallel. */
  if (mDistributedMesh) { DMDestroy(&dm); }
  else { mDistributedMesh = dm; }

  DMGetDimension(mDistributedMesh, &mNumDim);
  // Get number of elements (duh.)
  DMPlexGetDepthStratum(mDistributedMesh, mNumDim, NULL, &mNumberElementsLocal);

}

PetscErrorCode SetSymmetries(DM dm, PetscSection s, int* user_Nc, int user_Nf, int user_k, int user_dim)
{
  PetscInt       f, o, i, j, k, c, d;
  DMLabel        depthLabel;
  PetscErrorCode ierr;

  PetscFunctionBegin;
  ierr = DMGetLabel(dm,"depth",&depthLabel);CHKERRQ(ierr);
  for (f = 0; f < user_Nf; f++) {
    PetscSectionSym sym;

    if (user_k < 3) continue; /* No symmetries needed for order < 3, because no cell, facet, edge or vertex has more than one node */
    ierr = PetscSectionSymCreateLabel(PetscObjectComm((PetscObject)s),depthLabel,&sym);CHKERRQ(ierr);

    for (d = 0; d <= user_dim; d++) {
      if (d == 1) {
        PetscInt        numDof  = user_k - 1;
        PetscInt        numComp = user_Nc[f];
        PetscInt        minOrnt = -2;
        PetscInt        maxOrnt = 2;
        PetscInt        **perms;

        ierr = PetscCalloc1(maxOrnt - minOrnt,&perms);CHKERRQ(ierr);
        for (o = minOrnt; o < maxOrnt; o++) {
          PetscInt *perm;

          if (o == -1 || !o) { /* identity */
            perms[o - minOrnt] = NULL;
          } else {
            ierr = PetscMalloc1(numDof * numComp, &perm);CHKERRQ(ierr);
            for (i = numDof - 1, k = 0; i >= 0; i--) {
              for (j = 0; j < numComp; j++, k++) perm[k] = i * numComp + j;
            }
            perms[o - minOrnt] = perm;
          }
        }
        ierr = PetscSectionSymLabelSetStratum(sym,d,numDof*numComp,minOrnt,maxOrnt,PETSC_OWN_POINTER,(const PetscInt **) perms,NULL);CHKERRQ(ierr);
      } else if (d == 2) {
        PetscInt        perEdge = user_k - 1;
        PetscInt        numDof  = perEdge * perEdge;
        PetscInt        numComp = user_Nc[f];
        PetscInt        minOrnt = -4;
        PetscInt        maxOrnt = 4;
        PetscInt        **perms;

        ierr = PetscCalloc1(maxOrnt-minOrnt,&perms);CHKERRQ(ierr);
        for (o = minOrnt; o < maxOrnt; o++) {
          PetscInt *perm;

          if (!o) continue; /* identity */
          ierr = PetscMalloc1(numDof * numComp, &perm);CHKERRQ(ierr);
          /* We want to perm[k] to list which *localArray* position the *sectionArray* position k should go to for the given orientation*/
          switch (o) {
          case 0:
            break; /* identity */
          case -4: /* flip along (-1,-1)--( 1, 1), which swaps edges 0 and 3 and edges 1 and 2.  This swaps the i and j variables */
            perm[0] = 1;
            perm[1] = 3;
            perm[2] = 0;
            perm[3] = 2;
            /* perm[0] = 2; */
            /* perm[1] = 3; */
            /* perm[2] = 0; */
            /* perm[3] = 1; */
            /* break; */
            for (i = 0, k = 0; i < perEdge; i++) {
              for (j = 0; j < perEdge; j++, k++) {
                for (c = 0; c < numComp; c++) {
                  /* perm[k * numComp + c] = (perEdge * j + i) * numComp + c; // old */
                  // swaps i&j and reverses i
                  perm[k * numComp + c] = (perEdge * j + (perEdge - 1 - i) ) * numComp + c; // new
                  // printf("i=%d,j=%d,c=%d,k=%d,perEdge=%d,numComp=%d\n",i,j,c,k,perEdge,numComp);
                  // printf("o:-4,perm[%d]=%d\n",k * numComp + c,perm[k * numComp + c]);
                }
              }
            }
            break;
          case -3: /* flip along (-1, 0)--( 1, 0), which swaps edges 0 and 2.  This reverses the i variable */
            perm[0] = 3;
            perm[1] = 2;
            perm[2] = 1;
            perm[3] = 0;
            /* break; */
            for (i = 0, k = 0; i < perEdge; i++) {
              for (j = 0; j < perEdge; j++, k++) {
                for (c = 0; c < numComp; c++) {
                  /* perm[k * numComp + c] = (perEdge * (perEdge - 1 - i) + j) * numComp + c; */

                  // reverses i & j
                  perm[k * numComp + c] = (perEdge * (perEdge - 1 - i) + (perEdge - 1 - j)) * numComp + c;
                  // printf("o:-3,perm[%d]=%d\n",k * numComp + c,perm[k * numComp + c]);
                }
              }
            }
            break;
          case -2: /* flip along ( 1,-1)--(-1, 1), which swaps edges 0 and 1 and edges 2 and 3.  This swaps the i and j variables and reverse both */
            perm[0] = 2;
            perm[1] = 0;
            perm[2] = 3;
            perm[3] = 1;
            /* break; */
            for (i = 0, k = 0; i < perEdge; i++) {
              for (j = 0; j < perEdge; j++, k++) {
                for (c = 0; c < numComp; c++) {
                  perm[k * numComp + c] = (perEdge * (perEdge - 1 - j) + (perEdge - 1 - i)) * numComp + c;
                  // swaps i&j and reverses j
                  perm[k * numComp + c] = (perEdge * (perEdge - 1 - j) + i) * numComp + c;
                  // printf("o:-2,perm[%d]=%d\n",k * numComp + c,perm[k * numComp + c]);
                }
              }
            }
            break;
          case -1: /* flip along ( 0,-1)--( 0, 1), which swaps edges 3 and 1.  This reverses the j variable */
            perm[0] = 0;
            perm[1] = 1;
            perm[2] = 2;
            perm[3] = 3;
            /* break; */
            for (i = 0, k = 0; i < perEdge; i++) {
              for (j = 0; j < perEdge; j++, k++) {
                for (c = 0; c < numComp; c++) {
                  /* perm[k * numComp + c] = (perEdge * i + (perEdge - 1 - j)) * numComp + c; */
                  // no swaps or reverses
                  perm[k * numComp + c] = (perEdge * i + j) * numComp + c;
                  // printf("o:-1,perm[%d]=%d\n",k * numComp + c,perm[k * numComp + c]);
                }
              }
            }
            break;
          case  1: /* rotate section edge 1 to local edge 0.  This swaps the i and j variables and then reverses the j variable */
            for (i = 0, k = 0; i < perEdge; i++) {
              for (j = 0; j < perEdge; j++, k++) {
                for (c = 0; c < numComp; c++) {
                  perm[k * numComp + c] = (perEdge * (perEdge - 1 - j) + i) * numComp + c;
                  // printf("o:1,perm[%d]=%d\n",k * numComp + c,perm[k * numComp + c]);
                }
              }
            }
            break;
          case  2: /* rotate section edge 2 to local edge 0.  This reverse both i and j variables */
            for (i = 0, k = 0; i < perEdge; i++) {
              for (j = 0; j < perEdge; j++, k++) {
                for (c = 0; c < numComp; c++) {
                  perm[k * numComp + c] = (perEdge * (perEdge - 1 - i) + (perEdge - 1 - j)) * numComp + c;
                }
              }
            }
            break;
          case  3: /* rotate section edge 3 to local edge 0.  This swaps the i and j variables and then reverses the i variable */
            for (i = 0, k = 0; i < perEdge; i++) {
              for (j = 0; j < perEdge; j++, k++) {
                for (c = 0; c < numComp; c++) {
                  perm[k * numComp + c] = (perEdge * j + (perEdge - 1 - i)) * numComp + c;
                }
              }
            }
            break;
          default:
            break;
          }
          perms[o - minOrnt] = perm;
        }
        ierr = PetscSectionSymLabelSetStratum(sym,d,numDof*numComp,minOrnt,maxOrnt,PETSC_OWN_POINTER,(const PetscInt **) perms,NULL);CHKERRQ(ierr);
      }
    }
    ierr = PetscSectionSetFieldSym(s,f,sym);CHKERRQ(ierr);
    ierr = PetscSectionSymDestroy(&sym);CHKERRQ(ierr);
  }
  ierr = PetscSectionViewFromOptions(s,NULL,"-section_with_sym_view");CHKERRQ(ierr);
  PetscFunctionReturn(0);
}

void Mesh::setupTopology(const unique_ptr<ExodusModel> &model,
                         const unique_ptr<Options> &options) {

  /* Ensure mesh was read. */
  if (!mNumDim) { throw std::runtime_error("Mesh appears to have zero dimensions. Have you called read()?"); }

  /* Find all the mesh boundaries. */
  DMLabel label; DMGetLabel(mDistributedMesh, "Face Sets", &label);
  PetscInt size; DMLabelGetNumValues(label, &size);
  IS idIS; DMLabelGetValueIS(label, &idIS);
  const PetscInt *ids; ISGetIndices(idIS, &ids);
  for (PetscInt i = 0; i < size; i++) {
    PetscInt numFaces; DMLabelGetStratumSize(label, ids[i], &numFaces);
    IS pointIs; DMLabelGetStratumIS(label, ids[i], &pointIs);
    const PetscInt *faces; ISGetIndices(pointIs, &faces);
    for (PetscInt j = 0; j < numFaces; j++) { mBndPts.insert(faces[j]); }
  }

  /* Walk through the mesh and extract element types. */
  for (PetscInt i = 0; i < mNumberElementsLocal; i++) {

    /* Get and save the type of element i. */
    RealMat vtx = getElementCoordinateClosure(i); RealVec ctr(vtx.cols());
    for (PetscInt j = 0; j < mNumDim; j++) { ctr(j) = vtx.col(j).mean(); }
    std::string type = model->getElementType(ctr); mPointFields[i].insert(type);

    /* Add the type of element i to all mesh points connected via the Hasse graph. */
    PetscInt num_pts; const PetscInt *pts = NULL;
    DMPlexGetCone(mDistributedMesh, i, &pts); DMPlexGetConeSize(mDistributedMesh, i, &num_pts);    
    for (PetscInt j = 0; j < num_pts; j++) {
      // add element type to point
      mPointFields[pts[j]].insert(type);
      // if this point `pts[j]` is on a boundary (`mBndPts`), add "boundary" to type of the point
      if (mBndPts.find(pts[j]) != mBndPts.end()) {
        mPointFields[pts[j]].insert("boundary");
      }
    }

    /* Finally, add the type type to the global fields. */
    mMeshFields.insert(type);

  }

}

void Mesh::setupGlobalDof( unique_ptr<Element> const &element,
                          unique_ptr<Options> const &options) {

  /* Mesh topology must be set up first. */
  if (!mMeshFields.size()) {
    throw std::runtime_error("Before setting up the degrees of freedom, you must attach the topology by "
                                 "calling setupTopology.");
  }

  /* Use the information extracted above to inform the global DOF layout. */
  PetscInt num_bc = 0;
  PetscInt poly_order = options->PolynomialOrder();
  PetscInt num_fields = mMeshFields.size();
  PetscInt *num_comps; PetscMalloc1(num_fields, &num_comps);
  {
    PetscInt i = 0;
    for (auto &f: mMeshFields) { num_comps[i] = numFieldPerPhysics(f); i++; }
  }
  PetscInt *num_dof; PetscMalloc1(num_fields * (mNumDim + 1), &num_dof);
  printf("num_fields * (mNumDim + 1) = %d * (%d + 1)\n",num_fields,mNumDim);
  /* For each field... */
  for (PetscInt f = 0; f < num_fields; f++) {

    /* For each element point... (vertex, edge, face, volume) */
    for (PetscInt d = 0; d < (mNumDim + 1); d++) {

      PetscInt index = f * (mNumDim + 1) + d;
      switch (d) {

        /* 0-dimensional points (vertices). */
        case(0):

          num_dof[index] = element->NumDofVtx() * num_comps[f];
          break;

        /* 1-dimensional points (edges). */
        case(1):

          num_dof[index] = element->NumDofEdg() * num_comps[f];
          break;

        /* 2-dimensional points (faces). */
        case(2):

          num_dof[index] = element->NumDofFac() * num_comps[f];
          break;

        /* 3-dimensional points (cells). */
        case(3):

          num_dof[index] = element->NumDofVol() * num_comps[f];
          break;

        default:
          throw std::runtime_error("Unrecognized dimension! Dim: " + std::to_string(d));

      }

    }
  }

  
  
  /* Generate the section which will define the global dofs. */
  DMPlexCreateSection(mDistributedMesh, mNumDim, num_fields, num_comps, num_dof,
                      num_bc, NULL, NULL, NULL, NULL, &mMeshSection);
  
  /* Attach some meta-information to the section. */
  {
    PetscInt i = 0;
    for (auto &f: mMeshFields) { PetscSectionSetFieldName(mMeshSection, i++, f.c_str()); }
  }

  /* Attach the section to our DM */
  DMSetDefaultSection(mDistributedMesh, mMeshSection);

  /* Only create a spectral basis if it makes sense. */
  if ((this->baseElementType() == "quad") ||
      (this->baseElementType() == "hex")) {
    SetSymmetries(mDistributedMesh, mMeshSection, num_comps, num_fields, poly_order, mNumDim);
    DMPlexCreateSpectralClosurePermutation(mDistributedMesh, NULL);
  }
  PetscFree(num_dof); 
  PetscFree(num_comps);
}

std::vector<PetscInt> Mesh::EdgeNumbers(const PetscInt elm) {

  std::vector<PetscInt> edges;
  /* Step up one level in the graph (reduce dim). */
  PetscInt csize; DMPlexGetConeSize(mDistributedMesh, elm, &csize);
  const PetscInt *cone; DMPlexGetCone(mDistributedMesh, elm, &cone);
  for (PetscInt i = 0; i < csize; i++) { edges.push_back(cone[i]); }
  return edges;

}

PetscInt Mesh::GetNeighbouringElement(const PetscInt interface, const PetscInt this_elm) const {

  PetscInt neighbour = -1;
  PetscInt ssize; DMPlexGetSupportSize(mDistributedMesh, interface, &ssize);
  const PetscInt *supp; DMPlexGetSupport(mDistributedMesh, interface, &supp);
  for (PetscInt i = 0; i < ssize; i++) {
    if (supp[i] != this_elm) { neighbour = supp[i]; }
  }
  if (neighbour == -1) { throw std::runtime_error(
        "Element " + std::to_string(this_elm) + " has no neighbour on face "
                   + std::to_string(interface)); }
  return neighbour;

}

std::vector<std::tuple<PetscInt,std::vector<std::string>>> Mesh::CouplingFields(
    const PetscInt elm) {

  std::vector<std::tuple<PetscInt,std::vector<std::string>>> couple;
  /* Step one level up in graph (reduce dim). */
  PetscInt csize; DMPlexGetConeSize(mDistributedMesh, elm, &csize);
  const PetscInt *cone; DMPlexGetCone(mDistributedMesh, elm, &cone);
  for (PetscInt i = 0; i < csize; i++) {
    /* Step through the support of each point (increase dim to element). */
    PetscInt ssize; DMPlexGetSupportSize(mDistributedMesh, cone[i], &ssize);
    const PetscInt *supp; DMPlexGetSupport(mDistributedMesh, cone[i], &supp);
    for (PetscInt j = 0; j < ssize; j++) {
      /* Get fields on this element, but skip parent element. */
      std::vector<std::string> fields;
      if (supp[j] == elm) { continue; }
      for (auto &f: mPointFields[supp[j]]) { fields.push_back(f); }
      couple.push_back(std::make_tuple(cone[i], fields));
    }
  }
  return couple;
}

std::vector<std::string> Mesh::TotalCouplingFields(const PetscInt elm) {

  std::set<std::string> coupling_fields;
  PetscInt num_pts; const PetscInt *pts = NULL;
  DMPlexGetCone(mDistributedMesh, elm, &pts); DMPlexGetConeSize(mDistributedMesh, elm, &num_pts);
  for (PetscInt j = 0; j < num_pts; j++) {
    for (auto &f: mPointFields[pts[j]]) {
      if (mPointFields[elm].find(f) == mPointFields[elm].end()) {
        coupling_fields.insert(f);
      }
    }
  }
  return std::vector<std::string> (coupling_fields.begin(), coupling_fields.end());

}

Eigen::MatrixXd Mesh::getElementCoordinateClosure(PetscInt elem_num) {

  Vec coord;
  DMGetCoordinatesLocal(mDistributedMesh, &coord);
  PetscSection coord_section;
  DMGetCoordinateSection(mDistributedMesh, &coord_section);

  PetscInt coord_buf_size;
  PetscReal *coord_buf = NULL;
  DMPlexVecGetClosure(mDistributedMesh, coord_section, coord, elem_num, &coord_buf_size, &coord_buf);

  int num_vtx = coord_buf_size / mNumDim;
  Eigen::MatrixXd vtx(num_vtx, mNumDim);
  for (int i = 0; i < num_vtx; i++) {
    vtx(i, 0) = coord_buf[mNumDim * i + 0];
    vtx(i, 1) = coord_buf[mNumDim * i + 1];
    if (mNumDim == 3) {
      vtx(i, 2) = coord_buf[mNumDim * i + 2];
    }
  }

  DMPlexVecRestoreClosure(mDistributedMesh, coord_section, coord, elem_num, &coord_buf_size, &coord_buf);
  return vtx;

}

PetscInt Mesh::numFieldPerPhysics(std::string physics) {
  PetscInt num;
    if (physics == "fluid") { num = 1; }
    else if (physics == "2delastic") { num = 2; }
    else if (physics == "3delastic") { num = 3; }
    else {
      throw std::runtime_error("Derived type " + physics + " is not known.");
    }
  return num;
}

std::string Mesh::baseElementType() {
  std::string type;
  RealMat vtx = getElementCoordinateClosure(0);
  if (vtx.rows() == 3) {
    type = "tri";
  } else if (vtx.rows() == 4 && mNumDim == 2) {
    type = "quad";
  } else if (vtx.rows() == 4 && mNumDim == 3) {
    type = "tet";
  } else if (vtx.rows() == 8 && mNumDim == 3) {
    type = "hex";
  } else {
    ERROR() << "Element type not detected: vtx.rows()=" << vtx.rows() << " and dim = " << mNumDim;
  }
  return type;
}

