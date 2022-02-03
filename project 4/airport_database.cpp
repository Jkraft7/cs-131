#include "airport_database.hpp"

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "airport.hpp"
#include "flight_route.hpp"

AirportDatabase::AirportDatabase(
    const std::string& airport_datafile,
    const std::string& flight_datafile) {
  // Read in the airport data from airport_datafile.
  std::ifstream airport_file_stream(airport_datafile, std::ios::binary);
  Airport airport = Airport("", 0.0, 0.0);
    while (!airport_file_stream.eof()) {
    airport_file_stream >> airport;

    assert(code_to_index_.size() == index_to_code_.size());
    code_to_index_.emplace(airport.code(), code_to_index_.size());
    index_to_code_.emplace(index_to_code_.size(), airport.code());
    code_to_airport_.emplace(airport.code(), airport);
  }

  // Read in the flight route data from flight_datafile.
  std::ifstream flight_file_stream(flight_datafile, std::ios::binary);
  FlightRoute route = FlightRoute("", "");
    while (!flight_file_stream.eof()) {
    flight_file_stream >> route;

    if (code_to_index_.find(route.code_one()) != code_to_index_.end() &&
        code_to_index_.find(route.code_two()) != code_to_index_.end()) {
      routes_.push_back(route);
    }
  }
}

Airport AirportDatabase::airport(const std::string& code) const {
  // When C++20 is adopted, this should be !code_to_airport_.contains(code).
  if (code_to_airport_.find(code) == code_to_airport_.end()) {
    throw std::invalid_argument("code does not exist: " + code);
  }
  return code_to_airport_.at(code);
}

int AirportDatabase::index(const std::string& code) const {
  // When C++20 is adopted, this should be !code_to_index_.contains(code).
  if (code_to_index_.find(code) == code_to_index_.end()) {
    throw std::invalid_argument("code does not exist: " + code);
  }
  return code_to_index_.at(code);
}

std::string AirportDatabase::code(const int index) const {
  // When C++20 is adopted, this should be !code_to_index_.contains(code).
  if (index_to_code_.find(index) == index_to_code_.end()) {
    throw std::invalid_argument(
        "index does not exist: " + std::to_string(index));
  }
  return index_to_code_.at(index);
}

std::vector<std::string> AirportDatabase::codes() const noexcept {
  std::vector<std::string> codes;
  for (const auto& code_and_index : code_to_index_) {
    codes.push_back(code_and_index.first);
  }
  return codes;
}

std::vector<FlightRoute> AirportDatabase::routes()
    const noexcept {
  return routes_;
}

int AirportDatabase::size() const noexcept {
  return code_to_index_.size();
}