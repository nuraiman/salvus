#include <iostream>
#include <Physics/AcousticNew.h>
#include <Element/Element.h>
#include <Element/HyperCube/QuadNew.h>
#include <Element/HyperCube/Quad/QuadP1.h>
#include "catch.h"

TEST_CASE("test_stride", "[stride/quad]") {

  double tr[] = {5, 6, 7, 8, 9};
  double ts[] = {1, 6, 11, 16, 21};

  Eigen::VectorXd test = Eigen::VectorXd::LinSpaced(25, 0, 24);
  REQUIRE(QuadNew<QuadP1>::rVectorStride(test, 1, 5, 5) == Eigen::Map<Eigen::VectorXd> (tr, 5));
  REQUIRE(QuadNew<QuadP1>::sVectorStride(test, 1, 5, 5) == Eigen::Map<Eigen::VectorXd> (ts, 5));

}