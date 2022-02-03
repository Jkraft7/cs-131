#ifndef _airport_database_hpp_
#define _airport_database_hpp_

#include <string>
#include <vector>
#include <unordered_map>

#include "airport.hpp"
#include "flight_route.hpp"

// The AirportDatabase class encapsulates a database of airports and flight
// routes between the airports. 
class AirportDatabase {
 public:
  //
  // Constructors and Destructors
  //

  // The constructor, constructing an airport database from the data in
  // `airport_datafile` and `flight_datafile`.
  AirportDatabase(
      const std::string& airport_datafile, const std::string& flight_datafile);

  // The copy constructor is the default.
  AirportDatabase(const AirportDatabase& other) = default;

  // The copy assignment operator is the default.
  AirportDatabase& operator=(const AirportDatabase& lhs) = default;

  // The destructor is the default.
  ~AirportDatabase() = default;

  //
  // Accessors
  //

  // Returns the Airport object for the airport with code `code`.
  //
  // Throws a std::invalid_argument exception if the database does not contain
  // the code.
  Airport airport(const std::string& code) const;

  // Returns the index of the Airport object for the airport with code `code`.
  //
  // Throws a std::invalid_argument exception if the database does not contain
  // the code.
  int index(const std::string& code) const;

  // Returns the (three letter) IATA airport code for the index^th airport in
  // the database.
  //
  // Throws a std::invalid_argument exception if index is not between 0 and
  // size(), inclusive.
  std::string code(const int index) const;

  // Returns the set of (three letter) IATA airport codes in the database.
  std::vector<std::string> codes() const noexcept;

  // Returns the (bidirectional) flight routes for the airports in the database.
  std::vector<FlightRoute> routes() const noexcept;

  // Returns the number of airports in this database.
  int size() const noexcept;
  
 private:
  // A map from (three letter) IATA airport code to Airport object.
  std::unordered_map<std::string, Airport> code_to_airport_;

  // A map from (three letter) IATA airport code to canonical index in the
  // database.
  std::unordered_map<std::string, int> code_to_index_;

  // A map from canonical index in the database to (three letter) IATA airport
  // code.
  std::unordered_map<int, std::string> index_to_code_;

  // A list of (bidirectional) flight routes for the airports in the database.
  std::vector<FlightRoute> routes_;
};

#endif