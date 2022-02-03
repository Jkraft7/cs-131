#ifndef _graph_traversal_test_hpp_
#define _graph_traversal_test_hpp_

#include "graph_traversal.hpp"

#include <limits>
#include <stdexcept>

#include "adjacency_list_graph.hpp"
#include "adjacency_matrix_graph.hpp"
#include "undirected_graph.hpp"
#include "doctest.hpp"

constexpr int kIntMax = std::numeric_limits<int>::max();

TEST_CASE("DistanceAtMostTwoInDirectedGraph") {
  SUBCASE("NegativeStartThrowsException") {
    AdjacencyMatrixGraph graph(4);
    CHECK_THROWS_AS(distance_at_most_two(graph, -1), std::range_error);
  }

  SUBCASE("TooBigStartThrowsException") {
    AdjacencyMatrixGraph graph(4);
    CHECK_THROWS_AS(distance_at_most_two(graph, 4), std::range_error);
    CHECK_THROWS_AS(distance_at_most_two(graph, 5), std::range_error);
  }

  SUBCASE("EmptyGraph") {
    AdjacencyMatrixGraph graph(4);

    CHECK_EQ(
        distance_at_most_two(graph, 0),
        std::vector<bool>({true, false, false, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 1),
        std::vector<bool>({false, true, false, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 2),
        std::vector<bool>({false, false, true, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 3),
        std::vector<bool>({false, false, false, true}));
  }

  SUBCASE("StraightPath") {
    AdjacencyMatrixGraph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    CHECK_EQ(
        distance_at_most_two(graph, 0),
        std::vector<bool>({true, true, true, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 1),
        std::vector<bool>({false, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 2),
        std::vector<bool>({false, false, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 3),
        std::vector<bool>({false, false, false, true}));
  }

  SUBCASE("CompleteGraph") {
    AdjacencyMatrixGraph graph(4);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        graph.add_edge(i, j);
      }
    }

    CHECK_EQ(
        distance_at_most_two(graph, 0),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 1),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 2),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 3),
        std::vector<bool>({true, true, true, true}));
  }
}

TEST_CASE("DistanceAtMostTwoInUndirectedGraph") {
  SUBCASE("NegativeStartThrowsException") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    CHECK_THROWS_AS(distance_at_most_two(graph, -1), std::range_error);
  }

  SUBCASE("TooBigStartThrowsException") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    CHECK_THROWS_AS(distance_at_most_two(graph, 4), std::range_error);
    CHECK_THROWS_AS(distance_at_most_two(graph, 5), std::range_error);
  }

  SUBCASE("EmptyGraph") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);

    CHECK_EQ(
        distance_at_most_two(graph, 0),
        std::vector<bool>({true, false, false, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 1),
        std::vector<bool>({false, true, false, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 2),
        std::vector<bool>({false, false, true, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 3),
        std::vector<bool>({false, false, false, true}));
  }

  SUBCASE("StraightPath") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    CHECK_EQ(
        distance_at_most_two(graph, 0),
        std::vector<bool>({true, true, true, false}));
    CHECK_EQ(
        distance_at_most_two(graph, 1),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 2),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 3),
        std::vector<bool>({false, true, true, true}));
  }

  SUBCASE("CompleteGraph") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        graph.add_edge(i, j);
      }
    }

    CHECK_EQ(
        distance_at_most_two(graph, 0),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 1),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 2),
        std::vector<bool>({true, true, true, true}));
    CHECK_EQ(
        distance_at_most_two(graph, 3),
        std::vector<bool>({true, true, true, true}));
  }
}

TEST_CASE("ShortestPathInDirectedGraph") {
  SUBCASE("NegativeStartThrowsException") {
    AdjacencyMatrixGraph graph(4);
    CHECK_THROWS_AS(shortest_path(graph, -1), std::range_error);
  }

  SUBCASE("TooBigStartThrowsException") {
    AdjacencyMatrixGraph graph(4);
    CHECK_THROWS_AS(shortest_path(graph, 4), std::range_error);
    CHECK_THROWS_AS(shortest_path(graph, 5), std::range_error);
  }

  SUBCASE("EmptyGraph") {
    AdjacencyMatrixGraph graph(4);

    CHECK_EQ(
        shortest_path(graph, 0),
        std::vector<int>({0, kIntMax, kIntMax, kIntMax}));
    CHECK_EQ(
        shortest_path(graph, 1),
        std::vector<int>({kIntMax, 0, kIntMax, kIntMax}));
    CHECK_EQ(
        shortest_path(graph, 2),
        std::vector<int>({kIntMax, kIntMax, 0, kIntMax}));
    CHECK_EQ(
        shortest_path(graph, 3),
        std::vector<int>({kIntMax, kIntMax, kIntMax, 0}));
  }

  SUBCASE("StraightPath") {
    AdjacencyMatrixGraph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    CHECK_EQ(
        shortest_path(graph, 0),
        std::vector<int>({0, 1, 2, 3}));
    CHECK_EQ(
        shortest_path(graph, 1),
        std::vector<int>({kIntMax, 0, 1, 2}));
    CHECK_EQ(
        shortest_path(graph, 2),
        std::vector<int>({kIntMax, kIntMax, 0, 1}));
    CHECK_EQ(
        shortest_path(graph, 3),
        std::vector<int>({kIntMax, kIntMax, kIntMax, 0}));
  }

  SUBCASE("CompleteGraph") {
    AdjacencyMatrixGraph graph(4);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        graph.add_edge(i, j);
      }
    }

    CHECK_EQ(shortest_path(graph, 0), std::vector<int>({0, 1, 1, 1}));
    CHECK_EQ(shortest_path(graph, 1), std::vector<int>({1, 0, 1, 1}));
    CHECK_EQ(shortest_path(graph, 2), std::vector<int>({1, 1, 0, 1}));
    CHECK_EQ(shortest_path(graph, 3), std::vector<int>({1, 1, 1, 0}));
  }
}

TEST_CASE("ShortestPathInUndirectedGraph") {
  SUBCASE("NegativeStartThrowsException") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    CHECK_THROWS_AS(shortest_path(graph, -1), std::range_error);
  }

  SUBCASE("TooBigStartThrowsException") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    CHECK_THROWS_AS(shortest_path(graph, 4), std::range_error);
    CHECK_THROWS_AS(shortest_path(graph, 5), std::range_error);
  }

  SUBCASE("EmptyGraph") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);

    CHECK_EQ(
        shortest_path(graph, 0),
        std::vector<int>({0, kIntMax, kIntMax, kIntMax}));
    CHECK_EQ(
        shortest_path(graph, 1),
        std::vector<int>({kIntMax, 0, kIntMax, kIntMax}));
    CHECK_EQ(
        shortest_path(graph, 2),
        std::vector<int>({kIntMax, kIntMax, 0, kIntMax}));
    CHECK_EQ(
        shortest_path(graph, 3),
        std::vector<int>({kIntMax, kIntMax, kIntMax, 0}));
  }

  SUBCASE("StraightPath") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    CHECK_EQ(shortest_path(graph, 0), std::vector<int>({0, 1, 2, 3}));
    CHECK_EQ(shortest_path(graph, 1), std::vector<int>({1, 0, 1, 2}));
    CHECK_EQ(shortest_path(graph, 2), std::vector<int>({2, 1, 0, 1}));
    CHECK_EQ(shortest_path(graph, 3), std::vector<int>({3, 2, 1, 0}));
  }

  SUBCASE("CompleteGraph") {
    UndirectedGraph<AdjacencyMatrixGraph> graph(4);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        graph.add_edge(i, j);
      }
    }

    CHECK_EQ(shortest_path(graph, 0), std::vector<int>({0, 1, 1, 1}));
    CHECK_EQ(shortest_path(graph, 1), std::vector<int>({1, 0, 1, 1}));
    CHECK_EQ(shortest_path(graph, 2), std::vector<int>({1, 1, 0, 1}));
    CHECK_EQ(shortest_path(graph, 3), std::vector<int>({1, 1, 1, 0}));
  }
}

#endif