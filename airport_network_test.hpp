#ifndef _airport_network_test_hpp_
#define _airport_network_test_hpp_

#include "airport_network.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "airport_database.hpp"
#include "doctest.hpp"

TEST_CASE("Constructor") {
  SUBCASE("SmallDatabase") {
    const AirportDatabase airport_database =
        AirportDatabase("small_data_airports.txt", "small_data_flights.txt");
    const AirportNetwork airport_network = AirportNetwork(airport_database);
    CHECK_EQ(airport_network.num_airports(), 9);
    CHECK_EQ(airport_network.num_flight_routes(), 7);
  }

  SUBCASE("BigDatabase") {
    const AirportDatabase airport_database =
        AirportDatabase("data_airports.txt", "data_flights.txt");
    const AirportNetwork airport_network = AirportNetwork(airport_database);
    CHECK_EQ(airport_network.num_airports(), 9086);
    CHECK_EQ(airport_network.num_flight_routes(), 18171);
  }
}

TEST_CASE("AtMostOneLayoverSmallDatabase") {
  const AirportDatabase airport_database =
      AirportDatabase("small_data_airports.txt", "small_data_flights.txt");
  const AirportNetwork airport_network = AirportNetwork(airport_database);

  SUBCASE("BadCodeThrowsException") {
    CHECK_THROWS_AS(
        airport_network.at_most_one_layover("ACO"), std::invalid_argument);
  }

  SUBCASE("SelfAirportIsIncluded") {
    std::vector<std::string> possible =
        airport_network.at_most_one_layover("LAX");
    CHECK_NE(
        std::find(possible.begin(), possible.end(), "LAX"), possible.end());
  }

  SUBCASE("DirectFlightAirportIsIncluded") {
    std::vector<std::string> possible =
        airport_network.at_most_one_layover("LAX");
    CHECK_NE(
        std::find(possible.begin(), possible.end(), "ORD"), possible.end());
  }

  SUBCASE("LayoverAirportIsIncluded") {
    std::vector<std::string> possible =
        airport_network.at_most_one_layover("LAX");
    CHECK_EQ(possible.size(), 7);
    CHECK_NE(
        std::find(possible.begin(), possible.end(), "DEC"), possible.end());
  }

  SUBCASE("IsolatedAirportIsSingleton") {
    std::vector<std::string> possible =
        airport_network.at_most_one_layover("PGF");
    CHECK_EQ(possible.size(), 1);
    CHECK_EQ(possible[0], "PGF");
  }
}

TEST_CASE("AtMostOneLayoverLargeDatabase") {
  const AirportDatabase airport_database =
      AirportDatabase("data_airports.txt", "data_flights.txt");
  const AirportNetwork airport_network = AirportNetwork(airport_database);

  SUBCASE("BadCodeThrowsException") {
    CHECK_THROWS_AS(
        airport_network.at_most_one_layover("ACO"), std::invalid_argument);
  }

  SUBCASE("SelfAirportIsIncluded") {
    std::vector<std::string> possible =
        airport_network.at_most_one_layover("LAX");
    CHECK_NE(
        std::find(possible.begin(), possible.end(), "LAX"), possible.end());
  }

  SUBCASE("DirectFlightAirportIsIncluded") {
    std::vector<std::string> possible =
        airport_network.at_most_one_layover("LAX");
    CHECK_NE(
        std::find(possible.begin(), possible.end(), "ORD"), possible.end());
  }

  SUBCASE("LayoverAirportIsIncluded") {
    std::vector<std::string> possible =
        airport_network.at_most_one_layover("LAX");
    CHECK_EQ(possible.size(), 1677);
    CHECK_NE(
        std::find(possible.begin(), possible.end(), "DEC"), possible.end());
  }
}

TEST_CASE("LeastDistanceSmallDatabase") {
  const AirportDatabase airport_database =
      AirportDatabase("small_data_airports.txt", "small_data_flights.txt");
  const AirportNetwork airport_network = AirportNetwork(airport_database);

  SUBCASE("BadCodeThrowsException") {
    CHECK_THROWS_AS(
        airport_network.least_distance("ACO"), std::invalid_argument);
  }

  SUBCASE("SelfAirportIsDistanceZero") {
    const std::vector<int> distances = airport_network.least_distance("LAX");
    CHECK_EQ(distances[airport_database.index("LAX")], 0);
  }

  SUBCASE("DirectFlightAirportIsGreatCircleDistance") {
    const std::vector<int> distances = airport_network.least_distance("LAX");
    CHECK_EQ(distances[airport_database.index("ORD")], 1739);
  }

  SUBCASE("LayoverAirportIsSumOfGreatCircleDistances") {
    const std::vector<int> distances = airport_network.least_distance("LAX");
    CHECK_EQ(distances[airport_database.index("DEC")], 1895);
  }

  SUBCASE("IsolatedAirportIsMaxInt") {
    const std::vector<int> distances = airport_network.least_distance("LAX");
    CHECK_EQ(
        distances[airport_database.index("PGF")],
        std::numeric_limits<int>::max());
  }
}

TEST_CASE("LeastDistanceLargeDatabase") {
  const AirportDatabase airport_database =
      AirportDatabase("data_airports.txt", "data_flights.txt");
  const AirportNetwork airport_network = AirportNetwork(airport_database);

  SUBCASE("BadCodeThrowsException") {
    CHECK_THROWS_AS(
        airport_network.least_distance("ACO"), std::invalid_argument);
  }

  SUBCASE("SelfAirportIsDistanceZero") {
    const std::vector<int> distances = airport_network.least_distance("LAX");
    CHECK_EQ(distances[airport_database.index("LAX")], 0);
  }

  SUBCASE("DirectFlightAirportIsGreatCircleDistance") {
    const std::vector<int> distances = airport_network.least_distance("LAX");
    CHECK_EQ(distances[airport_database.index("ORD")], 1739);
  }

  SUBCASE("LayoverAirportIsSumOfGreatCircleDistances") {
    const std::vector<int> distances = airport_network.least_distance("LAX");
    CHECK_EQ(distances[airport_database.index("DEC")], 1696);
  }
}

#endif