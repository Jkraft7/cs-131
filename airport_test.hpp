#ifndef _airport_test_hpp_
#define _airport_test_hpp_

#include "airport.hpp"

#include <exception>

#include "doctest.hpp"

TEST_CASE("Accessors") {
  Airport airport = Airport("ABC", 1.2345, -5.4321);

  SUBCASE("Code") {
    CHECK_EQ(airport.code(), "ABC");
  }
  
  SUBCASE("Latitude") {
    CHECK_EQ(airport.latitude(), doctest::Approx(1.2345));
  }

  SUBCASE("Longitude") {
    CHECK_EQ(airport.longitude(), doctest::Approx(-5.4321));
  }
}

TEST_CASE("DistanceMiles") {
  Airport lax = Airport("LAX", 33.942501, -118.407997);
  Airport ord = Airport("ORD", 41.9786, -87.9048);

  CHECK_EQ(lax.distance_miles(ord), 1739);
  CHECK_EQ(ord.distance_miles(lax), 1739);
}

#endif