#include <Model/ExodusModel.h>
#include <Physics/AcousticElastic2D.h>
#include <Utilities/Options.h>
#include <Mesh/Mesh.h>

using namespace Eigen;

template <typename BasePhysics>
AcousticToElastic2D<BasePhysics>::AcousticToElastic2D(Options options): BasePhysics(options) {
}

template <typename BasePhysics>
std::vector<std::string> AcousticToElastic2D<BasePhysics>::PullElementalFields() const {
  return {"ux", "uy", "v"};
}

template <typename BasePhysics>
void AcousticToElastic2D<BasePhysics>::setBoundaryConditions(Mesh *mesh) {
  for (auto e: mesh->CouplingFields(BasePhysics::ElmNum())) {
    mEdg.push_back(std::get<0>(e));
    mNbr.push_back(mesh->GetNeighbouringElement(mEdg.back(), BasePhysics::ElmNum()));
    mNbrCtr.push_back(mesh->getElementCoordinateClosure(mNbr.back()).colwise().mean());
  }
  BasePhysics::setBoundaryConditions(mesh);
}

template <typename BasePhysics>
void AcousticToElastic2D<BasePhysics>::attachMaterialPropertiesNew(const ExodusModel *model) {

  for (auto ctr: mNbrCtr) {
    double rho_0 = 0;
    for (int i = 0; i < BasePhysics::NumVtx(); i++) {
      rho_0 += model->getElementalMaterialParameterAtVertex(ctr, "RHO", i);
    }
    mRho_0.push_back(rho_0 / BasePhysics::NumVtx());
  }

  // call parent.
  BasePhysics::attachMaterialPropertiesNew(model);

}

template <typename BasePhysics>
Eigen::MatrixXd AcousticToElastic2D<BasePhysics>::computeSurfaceIntegral(const Eigen::Ref<const Eigen::MatrixXd> &u) {

  // col0->ux, col1->uy, col2->potential.
  Eigen::MatrixXd rval = Eigen::MatrixXd::Zero(BasePhysics::NumIntPnt(), 2);
  for (int i = 0; i < mEdg.size(); i++) {
    rval.col(0) += mRho_0[i] * BasePhysics::applyTestAndIntegrateEdge(u.col(2), mEdg[i]);
    rval.col(1) += mRho_0[i] * BasePhysics::applyTestAndIntegrateEdge(u.col(2), mEdg[i]);
  }

  return -1 * rval;

}

#include <Physics/Elastic2D.h>
#include <Element/HyperCube/Quad.h>
#include <Element/HyperCube/QuadP1.h>
template class AcousticToElastic2D<Elastic2D<Quad<QuadP1>>>;