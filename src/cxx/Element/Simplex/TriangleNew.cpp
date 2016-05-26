
#include <mpi.h>
#include <iostream>
#include <petscdm.h>
#include <petscdmplex.h>
#include <tuple>
#include "TriangleNew.h"
#include <Element/Simplex/Triangle/TriP1.h>

using namespace Eigen;
/*
 * STATIC variables WHICH ARE ONLY ON THE REFERENCE ELEMENT.
 */
template <typename ConcreteShape>
MatrixXd TriangleNew<ConcreteShape>::mGradientPhi_dr;
template <typename ConcreteShape>
MatrixXd TriangleNew<ConcreteShape>::mGradientPhi_ds;

template <typename ConcreteShape>    
std::tuple<VectorXd,VectorXd> TriangleNew<ConcreteShape>::QuadraturePoints(const int order) {

  if(order == 3) {
    int num_pts = 12;
    VectorXd rn(num_pts);
    VectorXd sn(num_pts);
    coordinates_p3_triangle_rn(rn.data());
    coordinates_p3_triangle_sn(sn.data());
    return std::make_tuple(rn,sn);
  }
  else {
    std::cerr << "ERROR: Order NOT implemented!...\n";
    MPI::COMM_WORLD.Abort(-1);
  }
    
}

template <typename ConcreteShape>
VectorXd TriangleNew<ConcreteShape>::QuadratureIntegrationWeight(const int order) {
    
  if(order == 3) {
    int num_pts = 12;
    VectorXd wn(num_pts);
    quadrature_weights_p3_triangle(wn.data());
    return wn;
  } else {
    std::cerr << "ERROR: Order NOT implemented!\n";
    MPI::COMM_WORLD.Abort(-1);
  }
}

template <typename ConcreteShape>
VectorXi TriangleNew<ConcreteShape>::ClosureMapping(const int order, const int dimension) {

  if(order == 3) {

    int num_pts = 12;

    VectorXi closure(num_pts);
    closure << 0,1,2,3,4,5,6,7,8,9,10,11;
    return closure;
        
  } else {
    std::cerr << "ERROR: Order NOT implemented!\n";
    MPI::COMM_WORLD.Abort(-1);
  }
    
}

template <typename ConcreteShape>
TriangleNew<ConcreteShape>::TriangleNew(Options options) {

  // Basic properties.
  mPlyOrd = options.PolynomialOrder();
  if(mPlyOrd == 3) {
    mNumIntPnt = 12;
    mNumDofEdg = 2;
    mNumDofFac = 3;
    mNumDofVol = 0;
  }
  else {
    std::cerr << "ERROR: Order NOT implemented!\n";
    MPI::COMM_WORLD.Abort(-1);
  }
        
  // Nodal collocation points on edge and surface
  mNumDofVtx = 1;
        
  // Integration points and weights
  std::tie(mIntegrationCoordinates_r,mIntegrationCoordinates_s) =
    TriangleNew<ConcreteShape>::QuadraturePoints(options.PolynomialOrder());        
  mIntegrationWeights = TriangleNew<ConcreteShape>::QuadratureIntegrationWeight(options.PolynomialOrder());
        
  mClsMap = TriangleNew<ConcreteShape>::ClosureMapping(options.PolynomialOrder(), mNumDim);
  setupGradientOperator();

  mDetJac.setZero(mNumIntPnt);
  mParWork.setZero(mNumIntPnt);
  mStiffWork.setZero(mNumIntPnt);
  mGradWork.setZero(mNumIntPnt, mNumDim);
  
}

template <typename ConcreteShape>
void TriangleNew<ConcreteShape>::attachVertexCoordinates(DM &distributed_mesh) {

  Vec coordinates_local;
  PetscInt coordinate_buffer_size;
  PetscSection coordinate_section;
  PetscReal *coordinates_buffer = NULL;

  DMGetCoordinatesLocal(distributed_mesh, &coordinates_local);
  DMGetCoordinateSection(distributed_mesh, &coordinate_section);
  DMPlexVecGetClosure(distributed_mesh, coordinate_section, coordinates_local, mElmNum,
                      &coordinate_buffer_size, &coordinates_buffer);
  std::vector<PetscReal> coordinates_element(coordinates_buffer, coordinates_buffer+coordinate_buffer_size);
  DMPlexVecRestoreClosure(distributed_mesh, coordinate_section, coordinates_local, mElmNum,
                          &coordinate_buffer_size, &coordinates_buffer);
    
  for (int i = 0; i < mNumVtx; i++) {        
    mVtxCrd(i,0) = coordinates_element[mNumDim*i+0];
    mVtxCrd(i,1) = coordinates_element[mNumDim*i+1];
  }

  // Save element center
  mElmCtr <<
    mVtxCrd.col(0).mean(),
    mVtxCrd.col(1).mean();
}


template <typename ConcreteShape>
void TriangleNew<ConcreteShape>::attachMaterialProperties(const ExodusModel *model, std::string parameter_name) {

  Vector3d material_at_vertices;

  for (auto i = 0; i < mNumVtx; i++) {
    material_at_vertices(i) = model->getElementalMaterialParameterAtVertex(mElmCtr, parameter_name, i);
  }
  mPar[parameter_name] = material_at_vertices;
}

template <typename ConcreteShape>
void TriangleNew<ConcreteShape>::attachSource(std::vector<std::shared_ptr<Source>> sources) {

  for (auto &source: sources) {
    if (ConcreteShape::checkHull(source->PhysicalLocationX(), source->PhysicalLocationZ(), mVtxCrd)) {
      Vector2d reference_location = ConcreteShape::inverseCoordinateTransform(source->PhysicalLocationX(),
                                                                                     source->PhysicalLocationZ(),
                                                                                     mVtxCrd);
      source->setReferenceLocationR(reference_location(0));
      source->setReferenceLocationS(reference_location(1));
      mSrc.push_back(source);
    }
  }

}

template <typename ConcreteShape>
MatrixXd TriangleNew<ConcreteShape>::buildStiffnessMatrix(VectorXd velocity) {

  Matrix2d invJ;
  double detJ;
  std::tie(invJ,detJ) = ConcreteShape::inverseJacobian(mVtxCrd);
  //Jinv= rx, sx,
  //      rz, sz;
  auto drdx = invJ(0,0);
  auto dsdx = invJ(0,1);
  auto drdz = invJ(1,0);
  auto dsdz = invJ(1,1);

  // build material on all nodes
  MatrixXd elementStiffnessMatrix(mNumIntPnt,mNumIntPnt);
    
  // interpolate velocity at all nodes
  // for(int i=0;i<mNumIntPnt;i++) {
  //   auto r = mIntegrationCoordinates_r[i];
  //   auto s = mIntegrationCoordinates_s[i];
  //   velocity(i) = interpolateAtPoint(r,s).dot(mMaterialVelocityAtVertices);
  // }  
  
  // loop over matrix(i,j)
  for(int i=0;i<mNumIntPnt;i++) {
      
    VectorXd dPhi_dr_i = mGradientPhi_dr.row(i);
    VectorXd dPhi_ds_i = mGradientPhi_ds.row(i);
    auto dPhi_dx_i = dPhi_dr_i*drdx + dPhi_ds_i*dsdx;
    auto dPhi_dz_i = dPhi_dr_i*drdz + dPhi_ds_i*dsdz;
    for(int j=0;j<mNumIntPnt;j++) {
      VectorXd dPhi_dr_j = mGradientPhi_dr.row(j);
      VectorXd dPhi_ds_j = mGradientPhi_ds.row(j);
      auto dPhi_dx_j = dPhi_dr_j*drdx + dPhi_ds_j*dsdx;
      auto dPhi_dz_j = dPhi_dr_j*drdz + dPhi_ds_j*dsdz;
            
      elementStiffnessMatrix(i,j) = detJ*mIntegrationWeights.dot((velocity.array().pow(2) * dPhi_dx_i.array() * dPhi_dx_j.array()).matrix()) +
        detJ*mIntegrationWeights.dot((velocity.array().pow(2) * dPhi_dz_i.array() * dPhi_dz_j.array()).matrix());
    }
  }
  return elementStiffnessMatrix;
}


template <typename ConcreteShape>
void TriangleNew<ConcreteShape>::setupGradientOperator() {

  if(mPlyOrd == 3) {
    mGradientPhi_dr.resize(mNumIntPnt,mNumIntPnt);
    mGradientPhi_ds.resize(mNumIntPnt,mNumIntPnt);
    dphi_dr_rsn_p3_triangle(mGradientPhi_dr.data());
    dphi_ds_rsn_p3_triangle(mGradientPhi_ds.data());
  } else {        
    std::cerr << "NOT implemented yet!\n";
    MPI::COMM_WORLD.Abort(-1);
  }
}

template <typename ConcreteShape>
double TriangleNew<ConcreteShape>::integrateField(const VectorXd &field) {

  double val = 0;
  Matrix<double,2,2> inverse_Jacobian;
  double detJ;
  std::tie(inverse_Jacobian,detJ) = ConcreteShape::inverseJacobian(mVtxCrd);
  val = detJ*field.dot(mIntegrationWeights);
  return val;

}

template <typename ConcreteShape>
void TriangleNew<ConcreteShape>::attachReceiver(std::vector<std::shared_ptr<Receiver>> &receivers) {
  printf("TODO: attachedReciever\n");
  exit(1);
}

template <typename ConcreteShape>
VectorXd TriangleNew<ConcreteShape>::applyTestAndIntegrate(const Ref<const VectorXd> &f) {

  double detJac;
  Matrix2d invJac;
  std::tie(invJac,detJac) = ConcreteShape::inverseJacobian(mVtxCrd);
  return detJac*mIntegrationWeights.array()*f.array();
}

template <typename ConcreteShape>
void TriangleNew<ConcreteShape>::setBoundaryConditions(Mesh *mesh) {
  mBndElm = false;
  for (auto &keys: mesh ->BoundaryElementFaces()) {
    auto boundary_name = keys.first;
    auto element_in_boundary = keys.second;
    if (element_in_boundary.find(mElmNum) != element_in_boundary.end()) {
      mBndElm = true;
      mBnd[boundary_name] = element_in_boundary[mElmNum];
    }
  }
}

template <typename ConcreteShape>
VectorXd TriangleNew<ConcreteShape>::getDeltaFunctionCoefficients(const double r, const double s) {
  std::cerr << "ERROR: Not implemented getDeltaFunctionCoefficients\n";
  exit(1);
}

template <typename ConcreteShape>
VectorXd TriangleNew<ConcreteShape>::ParAtIntPts(const std::string &par) {

  // interpolate velocity at all nodes
  for(int i=0;i<mNumIntPnt;i++) {
    auto r = mIntegrationCoordinates_r[i];
    auto s = mIntegrationCoordinates_s[i];
    mParWork(i) = ConcreteShape::interpolateAtPoint(r,s).dot(mPar[par]);
  }  
  
  // for (int s_ind = 0; s_ind < mNumIntPtsS; s_ind++) {
  //   for (int r_ind = 0; r_ind < mNumIntPtsR; r_ind++) {

  //     double r = mIntCrdR(r_ind);
  //     double s = mIntCrdS(s_ind);
  //     mParWork(r_ind + s_ind*mNumIntPtsR) = ConcreteShape::interpolateAtPoint(r,s).dot(mPar[par]);

  //   }
  // }
  
  return mParWork;
}


template <typename ConcreteShape>
void TriangleNew<ConcreteShape>::applyDirichletBoundaries(Mesh *mesh, Options &options, const std::string &fieldname) {

  if (! mBndElm) return;

  double value = 0;
  auto dirchlet_boundary_names = options.DirichletBoundaries();
  for (auto &bndry: dirchlet_boundary_names) {
    auto faceids = mBnd[bndry];
    for (auto &faceid: faceids) {
      auto field = mesh->getFieldOnFace(fieldname, faceid);
      field = 0 * field.array() + value;
      mesh->setFieldFromFace(fieldname, faceid, field);
    }
  }
}

// Instantiate combinatorical cases.
template class TriangleNew<TriP1>;