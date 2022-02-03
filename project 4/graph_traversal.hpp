#ifndef _graph_traversal_hpp_
#define _graph_traversal_hpp_

#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#include "adjacency_list_graph.hpp"
#include "adjacency_matrix_graph.hpp"
#include "undirected_graph.hpp"

// Returns whether each vertex in the graph is at most distance two from vertex
// start.
//
// A vertex i is at most distance two from vertex start if any of the following
// is true:
//
// * The vertex i is vertex start, i.e., i == start. In this case, vertex i is
//   distance zero from vertex start.
// * There is an edge from vertex start to vertex i. In this case, vertex i is
//   distance one from vertex start.
// * There is another vertex j with an edge from vertex start to vertex j and
//   an edge from vertex j to vertex i. In this case, vertex i is distance two
//   from vertex start.
//
// Throws a std::invalid_argument exception if start is not a valid vertex.
//
// ASSUMES: The edge weights in graph are non-negative.
template <class Graph>
std::vector<bool> distance_at_most_two(const Graph& graph, const int start);

// Returns for each vertex in the graph the length of the shortest path from
// vertex start to the vertex.
//
// The i^th value in the return vector is the length of the shortest path from
// vertex start to vertex i (if a path exists) and
// std::numeric_limits<int>::max() otherwise (if no path exists).
//
// Throws a std::invalid_argument exception if start is not a valid vertex.
//
// ASSUMES: The edge weights in graph are non-negative.
template <class Graph>
std::vector<int> shortest_path(const Graph& graph, const int start);

#endif