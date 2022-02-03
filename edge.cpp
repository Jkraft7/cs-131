#include "edge.hpp"

#include <stdexcept>

Edge::Edge(const int i, const int j, const int weight)
    : i_(i), j_(j), weight_(weight) {
  if (weight == 0) {
    throw std::invalid_argument("weight must be non-zero");
  }
}

int Edge::i() const noexcept {
  return i_;
}

int Edge::j() const noexcept {
  return j_;
}

int Edge::weight() const noexcept {
  return weight_;
}

void Edge::set_weight(const int weight) {
  if (weight == 0) {
    throw std::invalid_argument("weight must be non-zero");
  }
  weight_ = weight;
}

bool Edge::operator==(const Edge& rhs) const noexcept {
  return i() == rhs.i() && j() == rhs.j() && weight() == rhs.weight();
}