#include "airport.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#include <math.h>

// Returns the number of radians equivalent to the number of degrees given.
double degrees_to_radians(const double degrees) {
  return M_PI / 180.0 * degrees;
}

// Returns the (great circle) distance in miles from this airport to `other`.
int Airport::distance_miles(const Airport& other) const {
  const int kEarthRadiusMiles = 3956;
  const double delta_latitude_radians =
     degrees_to_radians(latitude() - other.latitude());
  const double delta_longitude_radians =
      degrees_to_radians(longitude() - other.longitude());
  const double a = pow(sin(delta_latitude_radians / 2.0), 2.0)
      + cos(degrees_to_radians(latitude()))
          * cos(degrees_to_radians(other.latitude()))
          * pow(sin(delta_longitude_radians / 2.0), 2.0);
  const double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
  return kEarthRadiusMiles * c;
}

std::istream& operator>>(std::istream& stream, Airport& airport) {
  std::string code;
  std::string name;
  double latitude;
  double longitude;

  stream >> std::quoted(code);
  stream.ignore(256, ',');
  stream >> std::quoted(name);
  stream.ignore(256, ',');
  stream >> latitude;
  stream.ignore(256, ',');
  stream >> longitude;

  airport = Airport(code, latitude, longitude);

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Airport& airport) {
  stream << std::quoted(airport.code()) << ','
         << std::quoted(airport.code()) << ','
         << airport.latitude() << ','
         << airport.longitude()
         << std::endl;
  return stream;
}