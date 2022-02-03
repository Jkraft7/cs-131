#ifndef _route_hpp_
#define _route_hpp_

#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

// The FlightRoute class encapsulates information about a (bidirectional) route
// between two airports.
class FlightRoute {
 public:
  //
  // Constructors and Destructors
  //

  // The constructor.
  FlightRoute(const std::string& code_one, const std::string& code_two)
    : code_one_(code_one), code_two_(code_two) {}

  // Delete the no argument constructor, as an airport must have a code,
  // latitude, and longitude.
  FlightRoute() = delete;

  // The copy constructor.
  FlightRoute(const FlightRoute& other) = default;

  // The copy assignment constructor.
  FlightRoute& operator=(const FlightRoute& lhs) = default;

  // The destructor.
  ~FlightRoute() = default;

  //
  // Accessors
  //

  // Returns the (three letter) IATA code for an airport at one end of the
  // flight route.
  std::string code_one() const noexcept {
    return code_one_;
  }

  // Returns the (three letter) IATA code for an airport at the other end of
  // the flight route.
  std::string code_two() const noexcept {
    return code_two_;
  }

 private:
  // The (three letter) IATA code for the airport at one end of the flight
  // route.
  std::string code_one_;

  // The (three letter) IATA code for the airport at the other end of the flight
  // route.
  std::string code_two_;

  friend std::ostream& operator<<(
      std::ostream& stream, const FlightRoute& flight_route);
  friend std::istream& operator>>(
      std::istream& stream, FlightRoute& flight_route);
};

#endif