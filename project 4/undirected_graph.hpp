#ifndef _undirected_graph_hpp_
#define _undirected_graph_hpp_

#include <algorithm>
#include <set>
#include <string>

#include "adjacency_list_graph.hpp"
#include "adjacency_matrix_graph.hpp"
#include "edge.hpp"

// The UndirectedGraph class implements the Graph ADT for an undirected graph.
//
// The template parameter T specifies the directed graph implementation that
// the undirected graph should be a container adapter over. The main idea of the
// implementation is that an edge between vertex i and vertex j in the
// undirected graph is represented by edges from vertex i to vertex j and from
// vertex j to vertex i in the directed graph.
template <class T>
class UndirectedGraph {
 public:
  //
  // Constructors and Destructors
  //

  // Delete the no argument constructor. It does not make sense to create a
  // graph without knowing how many vertices there are.
  UndirectedGraph() = delete;

  // The constructor. Creates a graph with vertex_count-many vertices and no
  // edges.
  UndirectedGraph(const int vertex_count);

  // The copy constructor.
  UndirectedGraph(const UndirectedGraph& other) = default;

  // The copy assignment constructor.
  UndirectedGraph& operator=(const UndirectedGraph& other) = default;

  // The move constructor.
  UndirectedGraph(UndirectedGraph&& other) = default;

  // The move assignment constructor.
  UndirectedGraph& operator=(UndirectedGraph&& other) = default;

  // The destructor.
  ~UndirectedGraph() = default;


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
  // The directed graph the undirected graph is a container adapter over.
  T directed_graph_;

  // The number of undirected edges in the graph.
  //
  // An edge between a vertex i and a vertex j counts as one edge.
  int undirected_edge_count_;
};

#endif