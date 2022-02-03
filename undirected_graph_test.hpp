#ifndef _undirected_graph_test_hpp_
#define _undirected_graph_test_hpp_

// Unit tests for the UndirectedGraph class.
#include "undirected_graph.hpp"

#include "adjacency_list_graph.hpp"
#include "adjacency_matrix_graph.hpp"
#include "doctest.hpp"
#include "edge_test.hpp"
#include "graph_adt_test.hpp"

TEST_CASE_TEMPLATE_DEFINE("UndirectedGraph", GraphT, UndirectedGraph) {
  SUBCASE("EmptyGraph") {
    UndirectedGraph<GraphT> empty(0);

    SUBCASE("HasZeroVertexCount") {
      CHECK_EQ(empty.vertex_count(), 0);
    }

    SUBCASE("HasZeroEdgeCount") {
      CHECK_EQ(empty.edge_count(), 0);
    }

    SUBCASE("HasEmptyEdgeSet") {
      CHECK(empty.edges().empty());
    }
  }

  SUBCASE("VerticesOnlyGraph") {
    UndirectedGraph<GraphT> graph(kNumVertices);

    SUBCASE("HasZeroVertexCount") {
      CHECK_EQ(graph.vertex_count(), kNumVertices);
    }

    SUBCASE("HasZeroEdgeCount") {
      CHECK_EQ(graph.edge_count(), 0);
    }

    SUBCASE("HasEmptyEdgeSet") {
      CHECK(graph.edges().empty());
    }

    SUBCASE("HasEdgeReturnsFalse") {
      for (int i = 0; i < kNumVertices; ++i) {
        for (int j = 0; j < kNumVertices; ++j) {
          CHECK_FALSE(graph.has_edge(i, j));
        }
      }
    }

    SUBCASE("EdgeWeightThrows") {
      for (int i = 0; i < kNumVertices; ++i) {
        for (int j = 0; j < kNumVertices; ++j) {
          CHECK_THROWS_AS(graph.edge_weight(i, j), std::invalid_argument);
        }
      }
    }

    SUBCASE("OutEdgesReturnsEmptyVector") {
      for (int i = 0; i < kNumVertices; ++i) {
        CHECK(graph.out_edges(i).empty());
      }
    }

    SUBCASE("InEdgesReturnsEmptyVector") {
      for (int j = 0; j < kNumVertices; ++j) {
        CHECK(graph.in_edges(j).empty());
      }
    }
  }

  SUBCASE("CompleteGraphs") {
    UndirectedGraph<GraphT> graph(kNumVertices);
    for (int i = 0; i < kNumVertices; ++i) {
      for (int j = 0; j < kNumVertices; ++j) {
        graph.add_edge(i, j, i + j + 1);
      }
    }

    SUBCASE("VertexCount") {
      CHECK_EQ(graph.vertex_count(), kNumVertices);
    }

    SUBCASE("EdgeCount") {
      CHECK_EQ(graph.edge_count(), kNumVertices * (kNumVertices + 1) / 2);
    }

    SUBCASE("HasEdgeReturnsTrue") {
      for (int i = 0; i < kNumVertices; ++i) {
        for (int j = 0; j < kNumVertices; ++j) {
          CHECK(graph.has_edge(i, j));
        }
      }
    }

    SUBCASE("EdgeWeightReturnsWeight") {
      for (int i = 0; i < kNumVertices; ++i) {
        for (int j = 0; j < kNumVertices; ++j) {
          CHECK_EQ(graph.edge_weight(i, j), i + j + 1);
        }
      }
    }

    SUBCASE("InEdgesReturnAllVertices") {
      for (int j = 0; j < kNumVertices; ++j) {
        const std::vector<int> in_edges = graph.in_edges(j);
        const std::set<int> actual_in_edges_set =
            std::set<int>(in_edges.begin(), in_edges.end());
        const std::set<int> expected_in_edges_set = {0, 1, 2, 3, 4};
        CHECK_EQ(actual_in_edges_set, expected_in_edges_set);
      }
    }

    SUBCASE("OutEdgesReturnAllVertices") {
      for (int i = 0; i < kNumVertices; ++i) {
        const std::vector<int> out_edges = graph.out_edges(i);
        const std::set<int> actual_out_edges_set =
            std::set<int>(out_edges.begin(), out_edges.end());
        const std::set<int> expected_out_edges_set = {0, 1, 2, 3, 4};
        CHECK_EQ(actual_out_edges_set, expected_out_edges_set);
      }
    }

    SUBCASE("EdgesReturnsAllEdges") {
      const std::vector<Edge> edges = graph.edges();
      CHECK_EQ(edges.size(), graph.edge_count());
      for (int i = 0; i < kNumVertices; ++i) {
        for (int j = i; j < kNumVertices; ++j) {
          CHECK_NE(
              std::find(edges.begin(), edges.end(), Edge(i, j, i + j + 1)),edges.end());
        }
      }
    }
  }
}

TEST_CASE_TEMPLATE_INVOKE(UndirectedGraph, AdjacencyListGraph);
TEST_CASE_TEMPLATE_INVOKE(UndirectedGraph, AdjacencyMatrixGraph);

#endif