#include <stdexcept>

#include <Element/Element.h>
#include <Element/ElementAdapter.h>

#include <Element/HyperCube/TensorQuad.h>
#include <Element/HyperCube/QuadP1.h>
#include <Element/Simplex/Triangle.h>
#include <Element/Simplex/TriP1.h>
#include <Element/Simplex/Tetrahedra.h>
#include <Element/Simplex/TetP1.h>
#include <Element/HyperCube/Hexahedra.h>
#include <Element/HyperCube/HexP1.h>

#include <Physics/Scalar.h>
#include <Physics/ScalarTri.h>
#include <Physics/Elastic2D.h>
#include <Physics/Elastic3D.h>
#include <Physics/AcousticElastic2D.h>
#include <Physics/ElasticAcoustic2D.h>
#include <Utilities/Utilities.h>
#include <Utilities/Logging.h>
#include <Physics/HomogeneousDirichlet.h>

enum elem_code { eQuad, eHex, eTri, eTet, eNotImplemented };
elem_code etype(const std::string &etype) {
  if (etype == "quad") return eQuad;
  if (etype == "hex")  return eHex;
  if (etype == "tri")  return eTri;
  if (etype == "tet")  return eTet;
  else return eNotImplemented;
}

enum phys_code {
  /* Pure fluid. */
  eFluid,
  /* Pure fluid on mesh boundary. */
  eFluidBoundaryHomoDirichlet,
  /* Pure 2d elastic. */
  eElastic2D,
  /* 2D elastic boundary. */
  eElastic2DBoundaryHomoDirichlet,
  /* Pure 3d elastic. */
  eElastic3D,
  /* 3D elastic boundary. */
  eElastic3DBoundaryHomoDirichlet,
  /* 2D fluid couple to base solid. */
  eFluidToSolid2D,
  /* 2D solid couple to base fluid. */
  eSolidToFluid2D,
  /* 2D solid couple to base fluid on boundary. */
  eSolidToFluidBoundary2DHomoDirichlet,
  /* 2D fluid couple to base solid on boundary. */
  eFluidToSolidBoundary2DHomoDirichlet,
  /* If nothing appropriate was found. */
  eError
};
phys_code ptype(const std::vector<std::string> &ptype, const std::vector<std::string> &ctype) {

  /* Turn coupling types into a set, as there may be multiple. */
  std::set<std::string> cset(ctype.begin(), ctype.end());

  if (!ptype.size() || ptype.size() > 1) {
    return eError;
  }
  else if (ptype[0] == "fluid") {
    if (cset.empty()) {
      return eFluid;
    } else if (cset.size() == 1) {
      if (cset.find("2delastic") != cset.end()) {
        return eSolidToFluid2D;
      } else if (cset.find("boundary_homo_dirichlet") != cset.end()) {
        return eFluidBoundaryHomoDirichlet;
      }
    } else if (cset.size() == 2) {
      if (cset.find("2delastic") != cset.end() &&
          cset.find("boundary_homo_dirichlet")  != cset.end()) {
        return eSolidToFluidBoundary2DHomoDirichlet;
      }
    } else {
      return eError;
    }
  }
  else if (ptype[0] == "2delastic") {
    if (cset.empty()) {
      return eElastic2D;
    }
    else if (cset.size() == 1) {
      if (cset.find("fluid") != cset.end()) {
        return eFluidToSolid2D;
      } else if (cset.find("boundary_homo_dirichlet") != cset.end()) {
        return eElastic2DBoundaryHomoDirichlet;
      }
    } else if (cset.size() == 2) {
      if ((cset.find("fluid") != cset.end()) &&
          (cset.find("boundary_homo_dirichlet") != cset.end())) {
        return eFluidToSolidBoundary2DHomoDirichlet;
      }
    } else {
      return eError;
    }
  }
  else if (ptype[0] == "3delastic") {
    if (cset.empty()) {
      return eElastic3D;
    } else if (cset.size() == 1) {
      if (cset.find("boundary_homo_dirichlet") != cset.end()) {
        return eElastic3DBoundaryHomoDirichlet;
      }
    } else {
      return eError;
    }
  }
  return eError;
}

std::unique_ptr<Element> Element::Factory(const std::string &shape,
                                          const std::vector<std::string> &physics_base,
                                          const std::vector<std::string> &physics_couple,
                                          std::unique_ptr<Options> const &options) {


  std::string base = physics_base[0], couple;
  for (auto &p: physics_couple) { couple += p + ", "; }

  switch (etype(shape)) {

    case eQuad:
      switch (ptype(physics_base, physics_couple)) {

        case eFluid:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  Scalar<
                      TensorQuad<
                          QuadP1>>>(options));

        case eElastic2D:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  Elastic2D<
                      TensorQuad<
                          QuadP1>>>(options));

        case eFluidBoundaryHomoDirichlet:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  HomogeneousDirichlet<
                      Scalar<
                          TensorQuad<
                              QuadP1>>>>(options));

        case eElastic2DBoundaryHomoDirichlet:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  HomogeneousDirichlet<
                      Elastic2D<
                          TensorQuad<
                              QuadP1>>>>(options));

        case eSolidToFluid2D:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  ElasticToAcoustic2D<
                      Scalar<
                          TensorQuad<
                              QuadP1>>>>(options));

        case eFluidToSolid2D:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  AcousticToElastic2D<
                      Elastic2D<
                          TensorQuad<
                              QuadP1>>>>(options));

        case eSolidToFluidBoundary2DHomoDirichlet:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  HomogeneousDirichlet<
                      ElasticToAcoustic2D<
                          Scalar<
                              TensorQuad<
                                  QuadP1>>>>>(options));

        case eFluidToSolidBoundary2DHomoDirichlet:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  HomogeneousDirichlet<
                      AcousticToElastic2D<
                          Elastic2D<
                              TensorQuad<
                                  QuadP1>>>>>(options));

        default:
          throw std::runtime_error("Element could not be built.\n"
                                   "Type:             quad\n"
                                   "Base physics:     " + base +"\n"
                                   "Coupling physics: " + couple);

      }
    case eTri:
      switch (ptype(physics_base, physics_couple)) {

        case eFluid:
          return std::unique_ptr<Element> (new ElementAdapter<
                                           ScalarTri<
                                           Scalar<
                                           Triangle<
                                           TriP1>>>>(options));
          break;
        case eFluidBoundaryHomoDirichlet:
          return std::unique_ptr<Element> (new ElementAdapter<
                                           HomogeneousDirichlet<
                                           ScalarTri<
                                           Scalar<
                                           Triangle<
                                           TriP1>>>>>(options));
          break;
        default:
          throw std::runtime_error("Element could not be built.\n"
                                   "Type:             tri\n"
                                   "Base physics:     " + base +"\n"
                                   "Coupling physics: " + couple);
          break;
      }
    
    case eHex:
      switch (ptype(physics_base, physics_couple)) {

        case eFluid:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  Scalar<
                      Hexahedra<
                          HexP1>>>(options));

        case eElastic3D:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  Elastic3D<
                      Hexahedra<
                          HexP1>>>(options));

        case eFluidBoundaryHomoDirichlet:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  HomogeneousDirichlet<
                      Scalar<
                          Hexahedra<
                              HexP1>>>>(options));

        case eElastic3DBoundaryHomoDirichlet:
          return std::unique_ptr<Element> (
              new ElementAdapter<
                  HomogeneousDirichlet<
                      Elastic3D<
                          Hexahedra<
                              HexP1>>>>(options));

        default:
          throw std::runtime_error("Element could not be built.\n"
                                   "Type:             quad\n"
                                   "Base physics:     " + base +"\n"
                                   "Coupling physics: " + couple);
          break;
      }

    case eTet:
      switch (ptype(physics_base, physics_couple)) {

        case eFluid:
          return std::unique_ptr<Element> (new ElementAdapter<
                                           Scalar<
                                           Tetrahedra<
                                           TetP1>>>(options));
          break;
        case eFluidBoundaryHomoDirichlet:
          return std::unique_ptr<Element> (new ElementAdapter<
                                           HomogeneousDirichlet<
                                           Scalar<
                                           Tetrahedra<
                                           TetP1>>>>(options));
          break;
        default:
          throw std::runtime_error("Element could not be built.\n"
                                   "Type:             tri\n"
                                   "Base physics:     " + base +"\n"
                                   "Coupling physics: " + couple);
          break;
      }
      
    default:
      throw std::runtime_error("Element could not be built.\n"
                               "Type:             \n" + shape + "\n"
                               "Base physics:     " + base +"\n"
                               "Coupling physics: " + couple);
      break;

  }

  throw std::runtime_error("Element shape not supported.");

}
