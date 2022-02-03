#ifndef _adjacency_matrix_graph_test_hpp_
#define _adjacency_matrix_graph_test_hpp_

// Unit tests for the AdjacencyMatrixGraph class.
#include "adjacency_matrix_graph.hpp"

#include "doctest.hpp"
#include "graph_adt_test.hpp"

TEST_CASE_TEMPLATE_INVOKE(test_id, AdjacencyMatrixGraph);

#endif