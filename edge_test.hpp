#ifndef _edge_test_hpp_
#define _edge_test_hpp_

#include "edge.hpp"

#include <exception>

#include "doctest.hpp"

TEST_CASE("Constructor") {
  SUBCASE("WithSpecifiedWeight") {
    Edge edge(1, 2, 3);
    CHECK_EQ(edge.i(), 1);
    CHECK_EQ(edge.j(), 2);
    CHECK_EQ(edge.weight(), 3);
  }

  SUBCASE("WithDefaultWeight") {
    Edge edge(3, 4);
    CHECK_EQ(edge.i(), 3);
    CHECK_EQ(edge.j(), 4);
    CHECK_EQ(edge.weight(), 1);
  }

  SUBCASE("WithZeroWeight") {
    CHECK_THROWS_AS(Edge(3, 4, 0), std::invalid_argument);
  }
}

TEST_CASE("SetWeight") {
  Edge edge(1, 2, 3);

  SUBCASE("WithNonZeroWeight") {
    edge.set_weight(4);
    CHECK_EQ(edge.weight(), 4);
  }

  SUBCASE("WithZeroWeight") {
    CHECK_THROWS_AS(edge.set_weight(0), std::invalid_argument);
  }
}

TEST_CASE("Loops") {
  Edge edge(1, 1, 3);

  SUBCASE("HaveEqualIAndJ") {
    CHECK_EQ(edge.i(), edge.j());
    CHECK_EQ(edge.i(), 1);
    CHECK_EQ(edge.j(), 1);
  }
}

#endif