#ifndef _edge_hpp_
#define _edge_hpp_

// The Edge class encapsulates a non-zero weighted edge from an outbound
// (source) vertex i to an inbound (desination) vertex j.
//
// The edge can be a loop, i.e., the case i == j is allowed.
class Edge {
 public:
  //
  // Constructors and Destructors
  //

  // The constructor.
  //
  // Throws an std::invalid_argument exception if weight is zero.
  Edge(const int i, const int j, const int weight = 1);

  // The copy constructor is the default.
  Edge(const Edge& other) = default;

  // The copy assignment constructor is the default.
  Edge& operator=(const Edge& rhs) = default;

  // The destructor is the default.
  ~Edge() = default;

  //
  // Accessors
  //

  // Returns the outbound (source) from vertex.
  int i() const noexcept;

  // Returns the inbound (destination) to vertex.
  int j() const noexcept;

  // Returns the weight of the edge.
  int weight() const noexcept;

  //
  // Modifiers
  //

  // Updates the weight of the edge.
  //
  // Throws an std::invalid_argument exception if weight is zero.
  void set_weight(const int weight);

  //
  // Relational Operators
  //

  // Returns whether two edges are equal (i.e., the vertices and weights are the same).
  bool operator==(const Edge& rhs) const noexcept;

 private:
  // The index of the outbound (source) vertex.
  int i_;

  // The index of the inbound (destination) vertex.
  int j_;

  // The (non-zero) weight of the edge.
  int weight_; 
};

#endif