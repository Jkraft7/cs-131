#include "flight_route.hpp"

#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

std::istream& operator>>(std::istream& stream, FlightRoute& flight_route) {
  std::string code_one;
  std::string code_two;

  stream >> std::quoted(code_one);
  stream.ignore(256, ',');
  stream >> std::quoted(code_two);

  flight_route = FlightRoute(code_one, code_two);

  return stream;
}

std::ostream& operator<<(
    std::ostream& stream, const FlightRoute& flight_route) {
  stream << std::quoted(flight_route.code_one()) << ','
         << std::quoted(flight_route.code_two())
         << std::endl;
  return stream;
}