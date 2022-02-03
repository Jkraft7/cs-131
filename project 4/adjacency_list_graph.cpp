#include "adjacency_list_graph.hpp"

#include <algorithm>
#include <exception>
#include <forward_list>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "edge.hpp"

AdjacencyListGraph::AdjacencyListGraph(const int vertex_count)
    : vertex_count_(vertex_count),
      edge_count_(0),
      edge_weights_(vertex_count, std::forward_list<Edge>()) {}

//
// Accessors
//

int AdjacencyListGraph::vertex_count() const noexcept {
  return edge_weights_.size();
}

int AdjacencyListGraph::edge_count() const noexcept {
  return edge_count_;
}

bool AdjacencyListGraph::has_edge(const int i, const int j) const {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  for (const Edge& edge : edge_weights_[i]) {
    if (j == edge.j()) {
      return true;
    }
  }
  return false;
}

int AdjacencyListGraph::edge_weight(const int i, const int j) const {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  for (const Edge& edge : edge_weights_[i]) {
    if (j == edge.j()) {
      return edge.weight();
    }
  }
  throw std::invalid_argument("no edge from i to j");
}

std::vector<int> AdjacencyListGraph::out_edges(const int i) const {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  std::vector<int> outs;
  for (const Edge& edge : edge_weights_[i]) {
    outs.push_back(edge.j());
  }
  return outs;
}

std::vector<int> AdjacencyListGraph::in_edges(const int j) const {
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  std::vector<int> ins;
  for (const std::forward_list<Edge>& list : edge_weights_) {
    for (const Edge& edge : list) {
      if (j == edge.j()) {
        ins.push_back(edge.i());
      }
    }
  }
  return ins;
}

std::vector<Edge> AdjacencyListGraph::edges() const noexcept {
  std::vector<Edge> edges;
  for (const std::forward_list<Edge>& list : edge_weights_) {
    for (const Edge& edge : list) {
      edges.push_back(edge);
    }
  }
  return edges;
}

//
// Modifiers
//

void AdjacencyListGraph::add_edge(
    const int i, const int j, const int edge_weight) {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  if (edge_weight == 0) {
    throw std::invalid_argument("edge weight cannot be zero");
  }
  for (Edge& edge : edge_weights_[i]) {
    if (j == edge.j()) {
      edge.set_weight(edge_weight);
      return;
    }
  }
  edge_count_++;
  edge_weights_[i].push_front(Edge(i, j, edge_weight));
}

  // Removes the edge from vertex i to vertex j.
  //
  // Throws if 0 <= i, j < vertex_count() is violated of if there is no edge
  // from vertex i to vertex j.
void AdjacencyListGraph::remove_edge(const int i, const int j) {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  for (std::forward_list<Edge>::iterator iter = edge_weights_[i].before_begin();
       std::next(iter) != edge_weights_[i].end(); ++iter) {
    const std::forward_list<Edge>::iterator next_iter = std::next(iter);
    if (next_iter->i() == i && next_iter->j() == j) {
      edge_weights_[i].erase_after(iter);
      edge_count_--;
      break;
    }
  }
  throw std::invalid_argument("no edge from i to j");
}