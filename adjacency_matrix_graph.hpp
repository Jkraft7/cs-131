#ifndef _adjacency_matrix_graph_hpp_
#define _adjacency_matrix_graph_hpp_

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "edge.hpp"

// The AdjacencyMatrixGraph class implements the Graph ADT using the adjacency
// matrix representation.
class AdjacencyMatrixGraph {
 public:
  //
  // Constructors and Destructors
  // 

  // The default constructor. Creates a graph with vertex_count-many vertices
  // and no edges.
  AdjacencyMatrixGraph(const int vertex_count);

  // The copy constructor.
  AdjacencyMatrixGraph(const AdjacencyMatrixGraph& other) = default;

  // The copy assignment constructor.
  AdjacencyMatrixGraph& operator=(const AdjacencyMatrixGraph& other) = default;

  // The move constructor.
  AdjacencyMatrixGraph(AdjacencyMatrixGraph&& other) = default;

  // The move assignment constructor.
  AdjacencyMatrixGraph& operator=(AdjacencyMatrixGraph&& other) = default;

  // The destructor.
  ~AdjacencyMatrixGraph() = default;

  //
  // Accessors
  //

  // Returns the number of vertices in the graph.
  int vertex_count() const noexcept;

  // Returns the number of edges in the graph.
  int edge_count() const noexcept;

  // Returns whether there is an edge from vertex i to vertex j.
  //
  // Throws if 0 <= i, j < vertex_count() is violated.
  bool has_edge(const int i, const int j) const;
  
  // Returns the weight of the edge from vertex i to vertex j.
  //
  // Throws if 0 <= i, j < vertex_count() is violated or if !has_edge(i, j).
  int edge_weight(const int i, const int j) const;

  // Returns the vertices j with an edge from vertex i to vertex j.
  //
  // Throws if 0 <= i < vertex_count() is violated.
  std::vector<int> out_edges(const int i) const;

  // Returns the vertices i with an edge from vertex i to vertex j.
  //
  // Throws if 0 <= j < vertex_count() is violated.
  std::vector<int> in_edges(const int j) const;

  // Returns the edges in the graph, as a vector of Edge's.
  std::vector<Edge> edges() const noexcept;

  //
  // Modifiers
  //

  // Adds a new edge from vertex i to vertex j with the specified edge weight.
  //
  // If there is already an edge from vertex i to vertex j, this updates the
  // edge weight of the existing edge to `edge_weight`.
  //
  // Throws if 0 <= i, j < vertex_count() is violated or if edge_weight is zero.
  void add_edge(const int i, const int j, const int edge_weight = 1);

  // Removes the edge from vertex i to vertex j.
  //
  // Throws if 0 <= i, j < vertex_count() is violated of if there is no edge
  // from vertex i to vertex j.
  void remove_edge(const int i, const int j);

 private:
  // The number of vertices in the graph.
  const int vertex_count_;

  // The number of edges in the graph.
  //
  // This is always equal to the number of non-zero entries in the matrix
  // edge_weights_.
  int edge_count_;

  // The adjacency matrix storing the edges in the graph.
  //
  // The value of edge_weights_[i][j] represents the weight of the edge from
  // vertex i to vertex j. A value of 0 represents that no edge is present from
  // vertex i to vertex j.
  std::vector<std::vector<int>> edge_weights_;
};

#endif