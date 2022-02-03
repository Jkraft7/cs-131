#ifndef _airport_hpp_
#define _airport_hpp_

#include <iomanip>
#include <iostream>
#include <string>

// The Airport class encapsulates information about an airport.
class Airport {
 public:
  // The constructor.
  Airport(
      const std::string& code, const double latitude, const double longitude)
    : code_(code), latitude_(latitude), longitude_(longitude) {}

  // Delete the no argument constructor, as an airport must have a code,
  // latitude, and longitude.
  Airport() = delete;

  // The copy constructor.
  Airport(const Airport& other) = default;

  // The copy assignment constructor.
  Airport& operator=(const Airport& lhs) = default;

  // The destructor.
  ~Airport() = default;

  // Returns the (three letter) IATA code of this airport.
  std::string code() const {
    return code_;
  }

  // Returns the latitude of this airport in degrees.
  double latitude() const {
    return latitude_;
  }

  // Returns the longitude of this airport, in degrees.
  double longitude() const {
    return longitude_;
  }

  // Returns the (great circle) distance in miles from this airport to `other`.
  int distance_miles(const Airport& other) const;

 private:
  // The (three letter) IATA code for the airport.
  std::string code_;

  // The latitude of the airport, in degrees.
  double latitude_;
  
  // The longitude of the airport, in degrees.
  double longitude_;

  friend std::ostream& operator<<(std::ostream& stream, const Airport& airport);
  friend std::istream& operator>>(std::istream& stream, Airport& airport);
};

#endif