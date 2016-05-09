//
// Created by Michael Afanasiev on 2016-01-30.
//

#include "Acoustic.h"

AcousticQuad::AcousticQuad(Options options): Quad(options) {

    // Allocate element vectors.
    mMssMat.setZero(mNumIntPnt);

    // Strain matrix.
    mElementStrain.setZero(2, mNumIntPnt);

}



Eigen::MatrixXd AcousticQuad::computeStiffnessTerm(const Eigen::MatrixXd &displacement) {

    // Current gll point.
    int itr = 0;

    // Data structures we'll need here. Static arrays are allocated for free.
    // TODO: Look into a better way to deal with the temporarily allocated vectors. I believe that due to
    // TODO: RVO the integratedStiffnessMatrix should be ok, but perhaps jacobian_determinant could be handled better.
    Eigen::Matrix<double,2,2> inverse_Jacobian;
    Eigen::MatrixXd velocity_gradient(2, mNumIntPnt);
    Eigen::VectorXd detJ(mNumIntPnt);
    Eigen::VectorXd integratedStiffnessMatrix(mNumIntPnt);
    Eigen::Matrix<double,2,2> Jinv;
    double detJi;
    Vector2d elementStrainEpsEta(2);
    
    // Loop over all GLL points once to calculate the gradient of the pressure (u).
    for (auto eta_index = 0; eta_index < mNumIntPtsEta; eta_index++) {
        for (auto eps_index = 0; eps_index < mNumIntPtsEps; eps_index++) {

            // Eps and eta coordinates.
            double eta = mIntCrdEta[eta_index];
            double eps = mIntCrdEps[eps_index];

            // Get Jacobian determinant and its inverse
            std::tie(Jinv,detJi) = inverseJacobianAtPoint(eps,eta);
            detJ[itr] = detJi;

            // Calculate gradient in (eps,eta). Save for kernel calculations.
            elementStrainEpsEta <<
              mGrd.row(eps_index).dot(epsVectorStride(displacement, eta_index)),
              mGrd.row(eta_index).dot(etaVectorStride(displacement, eps_index));

            // (eps,eta) -> (x,z) and save for kernel calculations.
            mElementStrain.col(itr) = Jinv*elementStrainEpsEta;
            
            // interpolate material parameters at this node.
            double velocity = interpolateAtPoint(eps, eta).dot(mMaterialVelocityAtVertices);

            // apply material velocity (note v^2)
            velocity_gradient.col(itr) = velocity * velocity * mElementStrain.col(itr);
            
            itr++;

        }
    }

    // Loop over all gll points again. Apply shape function derivative and integrate.
    itr = 0;
    
    for (auto eta_index = 0; eta_index < mNumIntPtsEta; eta_index++) {
        for (auto eps_index = 0; eps_index < mNumIntPtsEps; eps_index++) {
            double eta = mIntCrdEta[eta_index];
            double eps = mIntCrdEps[eps_index];
            
            std::tie(Jinv,detJi) = inverseJacobianAtPoint(eps,eta);

            // apply gradient in reference coordinates (eps,eta)
            auto l_eps = mGrd.col(eps_index);
            auto l_eta = mGrd.col(eta_index);

            auto dphi_eps_dux = mIntWgtEta(eta_index) *
              mIntWgtEps.dot(((epsVectorStride(detJ, eta_index)).array() *
                              (epsVectorStride(velocity_gradient.row(0), eta_index)).array() *
                              (l_eps).array()).matrix());

            auto dphi_eta_dux = mIntWgtEps(eps_index) *
              mIntWgtEta.dot(((etaVectorStride(detJ, eps_index)).array() *
                              (etaVectorStride(velocity_gradient.row(0), eps_index)).array() *
                              (l_eta).array()).matrix());
            
            auto dphi_eps_duz = mIntWgtEta(eta_index) *
              mIntWgtEps.dot(((epsVectorStride(detJ, eta_index)).array() *
                              (epsVectorStride(velocity_gradient.row(1), eta_index)).array() *
                              (l_eps).array()).matrix());

            auto dphi_eta_duz = mIntWgtEps(eps_index) *
              mIntWgtEta.dot(((etaVectorStride(detJ, eps_index)).array() *
                              (etaVectorStride(velocity_gradient.row(1), eps_index)).array() *
                              (l_eta).array()).matrix());

            Vector2d dphi_epseta_dux(2);
            dphi_epseta_dux << dphi_eps_dux, dphi_eta_dux;

            Vector2d dphi_epseta_duz(2);
            dphi_epseta_duz << dphi_eps_duz, dphi_eta_duz;

            // from reference (eps,eta) to (x,z) coordinates
            integratedStiffnessMatrix(itr) =
              Jinv.row(0).dot(dphi_epseta_dux) +
              Jinv.row(1).dot(dphi_epseta_duz);
            
            itr++;
            
        }
    }

    return integratedStiffnessMatrix;
}

void AcousticQuad::attachMaterialProperties(ExodusModel *model) {

    // Vp (m/s).
    mMaterialVelocityAtVertices = __attachMaterialProperties(model, "VP");

}

Eigen::MatrixXd AcousticQuad::computeSourceTerm(double time) {

    // Initialize source vector (note: due to RVO I believe no memory re-allocation is occuring).
    Eigen::VectorXd F = Eigen::VectorXd::Zero(mNumIntPnt);

    // For all sources tagging along with this element.
    for (auto &source: mSrc) {

        // TODO: May make this more efficient (i.e. allocation every loop)?
        // Evaluate shape functions at source (eps, eta). Save the lagrange coefficients in current_source.
        Eigen::VectorXd current_source = interpolateLagrangePolynomials(
                source->ReferenceLocationEps(), source->ReferenceLocationEta(), mPlyOrd);

        // Loop over gll points
        for (auto eta_index = 0; eta_index < mNumIntPtsEta; eta_index++) {
            for (auto eps_index = 0; eps_index < mNumIntPtsEps; eps_index++) {

                double eps = mIntCrdEps[eps_index];
                double eta = mIntCrdEta[eta_index];

                double detJ;
                Eigen::Matrix2d Jinv;
                std::tie(Jinv, detJ) = inverseJacobianAtPoint(eps,eta);

                // Calculate the coefficients needed to integrate to the delta function.
                current_source[eps_index + eta_index*mNumIntPtsEps] /=
                    (mIntWgtEps(eps_index) * mIntWgtEta(eta_index) * detJ);


            }
        }

        // Scale by the source amplitude.
        current_source *= source->fire(time);
        F += current_source;

    }

    return F;
}

void AcousticQuad::computeSurfaceTerm() {
    std::cout << mElmNum << std::endl;
}

void AcousticQuad::assembleElementMassMatrix(Mesh *mesh) {

    int i=0;
    Eigen::Matrix<double,2,2> Jinv;
    double detJ;
    Eigen::VectorXd elementMassMatrix(mNumIntPnt);
    for (auto eta_index = 0; eta_index < mNumIntPtsEta; eta_index++) {
        for (auto eps_index = 0; eps_index < mNumIntPtsEps; eps_index++) {
            double eps = mIntCrdEps[eps_index];
            double eta = mIntCrdEta[eta_index];
            std::tie(Jinv,detJ) = inverseJacobianAtPoint(eps,eta);
            elementMassMatrix[i] = detJ * mIntWgtEps[eps_index] * mIntWgtEta[eta_index];
            i++;
        }
    }
    // assemble to shared nodes
    mesh->addFieldFromElement("m", mElmNum, mClsMap, elementMassMatrix);
}

double AcousticQuad::checkTest(Mesh* mesh, Options options, const Eigen::MatrixXd &displacement, double time) {
    auto u_current = displacement.col(0);
    // exact solution
    Eigen::VectorXd pts_x,pts_z;
    std::tie(pts_x,pts_z) = buildNodalPoints();
    auto un_exact = exactSolution(pts_x,pts_z,
                                  options.IC_SquareSide_L(),
                                  options.IC_Center_x(),options.IC_Center_z(),
                                  time);
    double element_error = (un_exact - u_current).array().abs().maxCoeff();
    return element_error;
}

void AcousticQuad::setupTest(Mesh* mesh, Options options) {
    Eigen::VectorXd pts_x,pts_z;
    std::tie(pts_x,pts_z) = buildNodalPoints();
    // push nodal locations to shared dofs
    setInitialCondition(mesh,pts_x,pts_z,
                        options.IC_SquareSide_L(),
                        options.IC_Center_x(),options.IC_Center_z());
}

void AcousticQuad::setInitialCondition(Mesh* mesh, Eigen::VectorXd& pts_x,Eigen::VectorXd& pts_z,
                                      double L, double x0, double z0) {
    
    double Lx = L;
    double Lz = L;
    const double PI = std::atan(1.0)*4.0;
    Eigen::VectorXd un = (PI/Lx*(pts_x.array()-(x0+L/2))).sin()*(PI/Lz*(pts_z.array()-(z0+L/2))).sin();
    Eigen::VectorXd vn = 0*pts_x;
    Eigen::VectorXd an = 0*pts_x;    
    mesh->setFieldFromElement("u", mElmNum, mClsMap, un);
    mesh->setFieldFromElement("v", mElmNum, mClsMap, vn);
    mesh->setFieldFromElement("a_", mElmNum, mClsMap, an);
    
}

Eigen::VectorXd AcousticQuad::exactSolution(Eigen::VectorXd& pts_x,Eigen::VectorXd& pts_z,
                                           double L, double x0, double z0, double time) {

    const double PI = std::atan(1.0)*4.0;
    double Lx = L;
    double Lz = L;
    Eigen::VectorXd un_xz = (PI/Lx*(pts_x.array()-(x0+L/2))).sin()*(PI/Lz*(pts_z.array()-(z0+L/2))).sin();
    double velocity = mMaterialVelocityAtVertices.mean();
    double un_t = cos(PI/Lx*sqrt(2)*time*velocity);
    return un_t*un_xz;
}
