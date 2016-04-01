//
// Created by Michael Afanasiev on 2016-03-27.
//

#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <Eigen/Dense>
#include <petsc.h>
#include <Element/Element.h>
#include <Element/HyperCube/Quad/Acoustic.h>

int main(int argc, char *argv[]) {

    // Init Salvus command line arguments.
    PetscInitialize(&argc, &argv, NULL, NULL);

    /* Need to be careful here. Catch defines its own command line
     * arguments, as does SALVUS. This is just a trick to get the
     * PETSc arguments read in, and then tell Catch that we really
     * don't have any command line arguments for it in particular.
     * */
    argc = 1;

    // Run all unit tests.
    int result = Catch::Session().run(argc, argv);

    // Clean up PETSc.
    PetscFinalize();

    return result;
}

Quad *setup_simple_quad(Options options) {

    // Simple model.
    ExodusModel *model = new ExodusModel(options);
    model->initializeParallel();

    // Get element from options.
    Element2D *reference_element = Element2D::factory(options);
    Quad *reference_quad = dynamic_cast<Quad*> (reference_element);

    // Make things easy by assuming a reference element.
    // NOTE THE ELEMENT IS DISTORTED x -> [-2, 1], y -> [-6, 1]
    Eigen::Matrix<double,2,4> coord;
    coord << -2, +1, +1, -2,
             -6, -6, +1, +1;
    reference_quad->SetVertexCoordinates(coord);
    reference_quad->attachMaterialProperties(model);
    reference_quad->setupGradientOperator();

    return reference_quad;

}

AcousticQuad* setup_simple_acousticquad(Options options) {

    // Get element from options.
    Element2D *reference_element = Element2D::factory(options);
    AcousticQuad *reference_quad = dynamic_cast<AcousticQuad*> (reference_element);

    // Make things easy by assuming a reference element.
    // NOTE THE ELEMENT IS DISTORTED x -> [-2, 1], y -> [-6, 1]
    Eigen::Matrix<double,2,4> coord;
    coord << -2, +1, +1, -2,
        -6, -6, +1, +1;
    reference_quad->SetVertexCoordinates(coord);
    return reference_quad;

}

TEST_CASE("Test whether simple stuff works.", "[element]") {

    Options options;
    options.setOptions();

    int max_order = 10;
    Eigen::VectorXd exact(max_order);
    exact <<    21/2.0, -21/4.0, -7.0, -10535/16.0,
                -1835099/400.0, -19962919/400.0,
                -177738369/400.0, -7111477851/1600.0,
                -207368760073/4800, -2094734230553/4800;
    for (int order = 1; order < max_order+1; order++) {

        options.__SetPolynomialOrder(order);
        Quad *reference_quad = setup_simple_quad(options);

        // Set up functions (order x**N*y**N-1)
        int ord = options.PolynomialOrder();
        Eigen::VectorXi x_exp = Eigen::VectorXi::LinSpaced(ord+1, 0, ord);
        Eigen::VectorXi y_exp = x_exp;
        y_exp[ord] = x_exp[ord - 1];

        // TODO: FIX THIS FUNCTION so that we don't need to pass it a mesh.
        Mesh *mesh;
        Eigen::VectorXd pts_x, pts_y;
        std::tie(pts_x,pts_y) = reference_quad->buildNodalPoints();

        // Set up function values at GLL points.
        double x, y;
        x = y = 0.0;
        Eigen::VectorXd gll_val;
        Eigen::VectorXd coords = Quad::GllPointsForOrder(options.PolynomialOrder());
        gll_val.setZero(reference_quad->NumberIntegrationPoints());
        int num_pts_p_dim = sqrt(reference_quad->NumberIntegrationPoints());
        for (int o = 0; o < x_exp.size(); o++) {
            for (int i = 0; i < num_pts_p_dim; i++) {
                for (int j = 0; j < num_pts_p_dim; j++) {

                    int ind = i + j * num_pts_p_dim;
                    gll_val(ind) += pow(pts_x(ind), x_exp(o)) * pow(pts_y(ind), y_exp(o));

                }
            }
        }

        // Test against analytical solution (from sympy), within floating point precision.
        REQUIRE(reference_quad->integrateField(gll_val) == Approx(exact(order-1)));
    }

}

TEST_CASE("Test quad velocity interpolation", "[element]") {

    Eigen::MatrixXd mMaterialVelocityAtVertices_i(3,4);
    mMaterialVelocityAtVertices_i <<
        1,2,2,1,
        1,1,2,2,
        1,1,2,1;
    
    Eigen::MatrixXd check_velocity_i(3,9);
    check_velocity_i <<
        1.0,1.5,2.0,1.0,1.5,2.0,1.0,1.5,2.0,
        1.0,1.0,1.0,1.5,1.5,1.5,2.0,2.0,2.0,
        1.0,1.0,1.0,1.0,1.25,1.5,1.0,1.5,2.0;
    
    for(int i=0;i<mMaterialVelocityAtVertices_i.rows();i++) {
        Eigen::VectorXd mMaterialVelocityAtVertices = mMaterialVelocityAtVertices_i.row(i);
        Eigen::VectorXd check_velocity = check_velocity_i.row(i);
        Options options;
        options.__SetPolynomialOrder(2);
    
        auto mIntegrationCoordinatesEta = Quad::GllPointsForOrder(options.PolynomialOrder());
        auto mIntegrationCoordinatesEps = Quad::GllPointsForOrder(options.PolynomialOrder());
        auto mNumberIntegrationPointsEta = mIntegrationCoordinatesEta.size();
        auto mNumberIntegrationPointsEps = mIntegrationCoordinatesEps.size();
    
        int n=0;
        Eigen::VectorXd velocity(mNumberIntegrationPointsEta*mNumberIntegrationPointsEps);
        for (auto eta_index = 0; eta_index < mNumberIntegrationPointsEta; eta_index++) {
            for (auto eps_index = 0; eps_index < mNumberIntegrationPointsEps; eps_index++) {

                // Eps and eta coordinates.
                double eta = mIntegrationCoordinatesEta[eta_index];
                double eps = mIntegrationCoordinatesEps[eps_index];
                // Get material parameters at this node.
                // new way
                auto interpolate1 = Quad::interpolateAtPoint(eps, eta);                
                velocity[n] = interpolate1.dot(mMaterialVelocityAtVertices);
                n++;
            }
        }
    
        REQUIRE((velocity.array()-check_velocity.array()).abs().maxCoeff() < 1e-5);
    }
}
