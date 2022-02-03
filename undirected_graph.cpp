#include "undirected_graph.hpp"

template <class T>
UndirectedGraph<T>::UndirectedGraph(const int vertex_count)
    : directed_graph_(vertex_count),
      undirected_edge_count_(0) {}

template <class T>
int UndirectedGraph<T>::vertex_count() const noexcept {
  return directed_graph_.vertex_count();
}

template <class T>
int UndirectedGraph<T>::edge_count() const noexcept {
  return undirected_edge_count_;
}

template <class T>
bool UndirectedGraph<T>::has_edge(const int i, const int j) const {
  return directed_graph_.has_edge(i, j);
}

template <class T>
int UndirectedGraph<T>::edge_weight(const int i, const int j) const {
  return directed_graph_.edge_weight(i, j);
}

template <class T>
std::vector<int> UndirectedGraph<T>::out_edges(const int i) const {
  // See the implementation comment within in_edges for discussion on why we
  // return out_edges here.
  return directed_graph_.out_edges(i);
}

template <class T>
std::vector<int> UndirectedGraph<T>::in_edges(const int j) const {
  // In a undirected graph, the in_edges and the out_edges for a vertex are the
  // same. Since 
  // (A) in_edges is O(m) and out_edges is O(deg(j)) for the adjacency list
  //     implementation
  // (B) in_edges is O(n) and out_edges is O(n) for the adjacency matrix
  //     implementation
  // we return out_edges(j) here as it is faster for (A) and the same for (B).
  return directed_graph_.out_edges(j);
}

template <class T>
std::vector<Edge> UndirectedGraph<T>::edges() const noexcept {
  std::vector<Edge> edges = directed_graph_.edges();
  // NOTE: In C++20, this would be more idiomatically accomplished using
  // std::erase_if.
  auto remove_iter = std::remove_if(
      edges.begin(),
      edges.end(),
      [](const Edge& edge) { return edge.i() > edge.j(); });
  edges.erase(remove_iter, edges.end());
  return edges;
}

template <class T>
void UndirectedGraph<T>::add_edge(
    const int i, const int j, const int edge_weight) {
  // If the edge does not already exist, then increment our undirected edge
  // count.
  if (!directed_graph_.has_edge(i, j)) {
    undirected_edge_count_++;
  }
  // Regardless of whether the edge already exists, we call add_edge on our
  // directed graph to add / update the edge_weight.
  if (i == j) {
    directed_graph_.add_edge(i, j, edge_weight);
  } else {
    directed_graph_.add_edge(i, j, edge_weight);
    directed_graph_.add_edge(j, i, edge_weight);
  }
}

template <class T>
void UndirectedGraph<T>::remove_edge(const int i, const int j) {
  // If i != j, we remove both the edge from vertex i to vertex j and the edge
  // from vertex j to vertex i from our directed graph. If i == j, these edges
  // are the same, so we only make one call to remove_edge.
  if (i == j) {
    directed_graph_.remove_edge(i, j);
  } else {
    directed_graph_.remove_edge(i, j);
    directed_graph_.remove_edge(j, i);
  }
  undirected_edge_count_--;
}

template class UndirectedGraph<AdjacencyListGraph>;
template class UndirectedGraph<AdjacencyMatrixGraph>;