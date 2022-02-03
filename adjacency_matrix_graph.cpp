#include "adjacency_matrix_graph.hpp"

#include <algorithm>
#include <exception>
#include <iterator>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

AdjacencyMatrixGraph::AdjacencyMatrixGraph(const int vertex_count)
    : vertex_count_(vertex_count),
      edge_count_(0),
      edge_weights_(vertex_count, std::vector<int>(vertex_count, 0)) {}

//
// Accessors
//

int AdjacencyMatrixGraph::vertex_count() const noexcept {
  return edge_weights_.size();
}

int AdjacencyMatrixGraph::edge_count() const noexcept {
  return edge_count_;
}

bool AdjacencyMatrixGraph::has_edge(const int i, const int j) const {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  return edge_weights_[i][j] != 0;
}

int AdjacencyMatrixGraph::edge_weight(const int i, const int j) const {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  if (!has_edge(i, j)) {
    throw std::invalid_argument("no edge from i to j");
  }
  return edge_weights_[i][j];
}

std::vector<int> AdjacencyMatrixGraph::out_edges(const int i) const {
  if (i < 0 || i >= vertex_count_) {
    throw std::range_error("invalid i: " + std::to_string(i));
  }
  std::vector<int> outs;
  for (int j = 0; j < vertex_count_; ++j) {
    if (edge_weights_[i][j] != 0) {
      outs.push_back(j);
    }
  }
  return outs;
}

std::vector<int> AdjacencyMatrixGraph::in_edges(const int j) const {
  if (j < 0 || j >= vertex_count_) {
    throw std::range_error("invalid j: " + std::to_string(j));
  }
  std::vector<int> ins;
  for (int i = 0; i < vertex_count_; ++i) {
    if (edge_weights_[i][j] != 0) {
      ins.push_back(i);
    }
  }
  return ins;
}

std::vector<Edge> AdjacencyMatrixGraph::edges() const noexcept {
  std::vector<Edge> edges;
  for (int i = 0; i < vertex_count_; ++i) {
    for (int j = 0; j < vertex_count_; ++j) {
      if (edge_weights_[i][j] != 0) {
        edges.push_back(Edge(i, j, edge_weights_[i][j]));
      }
    }
  }
  return edges;
}

//
// Modifiers
//

void AdjacencyMatrixGraph::add_edge(
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
  if (has_edge(i, j)) {
    edge_weights_[i][j] = edge_weight;
    return;
  }
  edge_count_++;
  edge_weights_[i][j] = edge_weight;
}

void AdjacencyMatrixGraph::remove_edge(const int i, const int j) {
  if (!has_edge(i, j)) {
    throw std::invalid_argument(
        "no edge from i to j to remove: " +
            std::to_string(i) + ", " + std::to_string(j));;
  }
  edge_weights_[i][j] = 0;
}