#include "catch.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Dense>
#include <petsc.h>

#include <Mesh/Mesh.h>
#include <Model/ExodusModel.h>

#include <Element/Element.h>
#include <Element/ElementAdapter.h>
#include <Element/HyperCube/QuadP1.h>
#include <Element/HyperCube/TensorQuad.h>

#include <Utilities/Types.h>
#include <Utilities/Options.h>

using namespace std;
using namespace Eigen;

TEST_CASE("Test tensor quad", "[tensor_quad]") {

  PetscOptionsClear();
  const char *arg[] = {
      "salvus_test",
      "--testing", "true",
      "--element_shape", "quad_new",
  };

  // Fake setting via command line.
  char **argv = const_cast<char **> (arg);
  int argc = sizeof(arg) / sizeof(const char *) - 1;
  PetscOptionsInsert(&argc, &argv, NULL);

  // Default vertices.
  QuadVtx vtx;
  vtx << -1, -1, +1, -1, +1, +1, -1, +1;

  // Initialize options.
  for (PetscInt i = 1; i < TensorQuad<QuadP1>::MaxOrder(); i++) {

    PetscOptionsSetValue("--polynomial_order", std::to_string(i).c_str());
    std::unique_ptr<Options> options(new Options);
    options->setOptions();

    TensorQuad<QuadP1> test_quad(options);
    test_quad.SetVtxCrd(vtx);
    RealVec locations = test_quad.GllPointsForOrder(i);
    PetscInt gll_per_dim = options->PolynomialOrder() + 1;

    // Define test quad and set up test fields.
    RealVec test_field = RealVec::Zero(test_quad.NumIntPnt());
    RealVec test_field_grad_x = RealVec::Zero(test_quad.NumIntPnt());
    RealVec test_field_grad_y = RealVec::Zero(test_quad.NumIntPnt());
    for (PetscInt j = 0; j < gll_per_dim; j++) {
      for (PetscInt k = 0; k < gll_per_dim; k++) {

        PetscReal r = locations(k);
        PetscReal s = locations(j);

        // x goes up to order N, y goes up to N-1
        for (PetscInt l = 0, m = 0; l < gll_per_dim; l++, m++) {
          if (m > gll_per_dim - 2) { m = gll_per_dim - 2; }
          test_field(k + j * gll_per_dim) += pow(locations(k), l) * pow(locations(j), m);
        }

        // df_dx analytic (see python analytic_integrals).
        for (PetscInt m = 1, x = 0, y = 1; m < gll_per_dim; x++, y++, m++) {
          y = min(gll_per_dim - 2, y);
          if (y > gll_per_dim - 2) { y = gll_per_dim - 2; }
          test_field_grad_x(k + j * gll_per_dim) +=
              m * pow(locations(k), x) * pow(locations(j), y);
        }

        // df_dy analytic (see python analytic_integrals).
        for (PetscInt m = 1, x = 1, y = 0; x < gll_per_dim; x++, y++, m++) {
          m = min(gll_per_dim - 2, m);
          y = min(gll_per_dim - 3, y);
          test_field_grad_y(k + j * gll_per_dim) +=
              m * pow(locations(k), x) * pow(locations(j), y);
        }

      }
    }

    // Test field gradients.
    REQUIRE(test_quad.computeGradient(test_field).col(0).isApprox(test_field_grad_x));
    REQUIRE(test_quad.computeGradient(test_field).col(1).isApprox(test_field_grad_y));

    // TODO: This needs to be improved.
    // Test integral of applyTestGradAndIntegrate.
    RealMat grad = test_quad.computeGradient(test_field);
    REQUIRE(test_quad.applyGradTestAndIntegrate(grad).sum() == Approx(0.0));

    // Interpolate lagrange polynomials at certain points.
    for (PetscInt j = 0; j < locations.size(); j++) {
      for (PetscInt k = 0; k < locations.size(); k++) {

        PetscReal r = locations(k);
        PetscReal s = locations(j);
        REQUIRE(test_quad.interpolateLagrangePolynomials(r, s, i)(k+j*locations.size())
                    == Approx(1.0));

      }
    }

  }





//
//
//
//
//
//
//  // Precision with which to compare matrices.
//  double precision = 1e-5;
//
//  // Matrix representing edge integral values.
//  MatrixXd QuadEdgeTrue = MatrixXd::Zero(25, 4);
//
//  QuadEdgeTrue(0,0)  = -235.65;
//  QuadEdgeTrue(1,0)  = -204.081;
//  QuadEdgeTrue(2,0)  = +28.2667;
//  QuadEdgeTrue(3,0)  = -23.9857;
//  QuadEdgeTrue(4,0)  = -60.15;
//
//  QuadEdgeTrue(4,1)  = -140.35;
//  QuadEdgeTrue(9,1)  = -382.667;
//  QuadEdgeTrue(14,1) = -65.9556;
//  QuadEdgeTrue(19,1) = +1.5562;
//  QuadEdgeTrue(24,1) = +1.75;
//
//  QuadEdgeTrue(20,2) = +1.65;
//  QuadEdgeTrue(21,2) = +2.68116;
//  QuadEdgeTrue(22,2) = +0.733333;
//  QuadEdgeTrue(23,2) = +1.53551;
//  QuadEdgeTrue(24,2) = +0.75;
//
//  QuadEdgeTrue(0,3)  = -549.85;
//  QuadEdgeTrue(5,3)  = -1481.61;
//  QuadEdgeTrue(10,3) = -233.956;
//  QuadEdgeTrue(15,3) = +2.89441;
//  QuadEdgeTrue(20,3) = +3.85;
//
//  // Set up custom command line arguments.
//  PetscOptionsClear();
//  const char *arg[] = {
//      "salvus_test",
//      "--testing", "true",
//      "--element_shape", "quad_new",
//      "--polynomial_order", "4", NULL
//  };
//
//  // Fake setting via command line.
//  char **argv = const_cast<char **> (arg);
//  int argc = sizeof(arg) / sizeof(const char *) - 1;
//  PetscOptionsInsert(&argc, &argv, NULL);
//
//  // Set vertices.
//  Eigen::Matrix<double,4,2> vtx;
//  vtx << -2, -6, +1, -6, +1, +1, -2, +1;
//
//  SECTION("Test edge integrals") {
//    // Some default set of coupling edges.
//    std::vector<PetscInt> cpl = {0, 1, 2, 3};
//
//    int max_order = 4;
//    for (int order = 4; order < max_order + 1; order++) {
//
//      std::string num = std::to_string((long long) order);
//      PetscOptionsSetValue("--polynomial_order", num.c_str());
//
//      // Initialize options.
//      std::unique_ptr<Options> options(new Options);
//      options->setOptions();
//
//      // Setup test element.
//      TestPlugin<TensorQuad<QuadP1>> basequad(options);
//      basequad.SetVtxCrd(vtx);
//      basequad.SetCplEdg(cpl);
//
//      // Set up functions (order x**n*y**N-1)
//      int ord = options->PolynomialOrder();
//      Eigen::VectorXi x_exp, y_exp;
//      x_exp = y_exp = Eigen::VectorXi::LinSpaced(ord + 1, 0, ord);
//      y_exp(ord) = x_exp(ord - 1);
//
//      Eigen::VectorXd pts_x, pts_y;
//      std::tie(pts_x, pts_y) = QuadP1::buildNodalPoints(
//          TensorQuad<QuadP1>::GllPointsForOrder(ord), TensorQuad<QuadP1>::GllPointsForOrder(ord), vtx);
//
//      // Set up functions at GLL points.
//      double x = 0, y = 0;
//      Eigen::VectorXd gll_val, coords = TensorQuad<QuadP1>::GllPointsForOrder(ord);
//      gll_val.setZero(basequad.NumIntPnt());
//      int num_pts_p_dim = sqrt(basequad.NumIntPnt());
//      for (int o = 0; o < x_exp.size(); o++) {
//        for (int i = 0; i < num_pts_p_dim; i++) {
//          for (int j = 0; j < num_pts_p_dim; j++) {
//
//            int ind = i + j * num_pts_p_dim;
//            gll_val(ind) += pow(pts_x(ind), x_exp(o)) * pow(pts_y(ind), y_exp(o));
//
//          }
//        }
//      }
//
//      for (int edge = 0; edge < 4; edge++) {
//        REQUIRE(QuadEdgeTrue.col(edge).isApprox(basequad.applyTestAndIntegrateEdge(gll_val, edge), precision));
//      }
//
//    }
//  }

}