#ifndef _adjacency_list_graph_hpp_
#define _adjacency_list_graph_hpp_

#include <forward_list>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "edge.hpp"

// The AdjacencyListGraph class implements the Graph ADT using the adjacency
// list representation.
class AdjacencyListGraph {
 public:
  //
  // Constructors and Destructors
  // 

  // The default constructor. Creates a graph with vertex_count-many vertices
  // and no edges.
  AdjacencyListGraph(const int vertex_count);

  // The copy constructor.
  AdjacencyListGraph(const AdjacencyListGraph& other) = default;

  // The copy assignment constructor.
  AdjacencyListGraph& operator=(const AdjacencyListGraph& other) = default;

  // The move constructor.
  AdjacencyListGraph(AdjacencyListGraph&& other) = default;

  // The move assignment constructor.
  AdjacencyListGraph& operator=(AdjacencyListGraph&& other) = default;

  // The destructor.
  ~AdjacencyListGraph() = default;

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

  // Returns the edges in the graph, as a vector of Edges.
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

  // The adjacency lists storing the edges in the graph.
  //
  // An Edge(j, edge_weight) will exist in i^th element of edge_weights_ 
  // (with edge_weight != 0) if there is an edge from vertex i to vertex j. 
  std::vector<std::forward_list<Edge>> edge_weights_;
};

#endif