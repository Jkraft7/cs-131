#ifndef _adjacency_list_graph_test_hpp_
#define _adjacency_list_graph_test_hpp_

// Unit tests for the AdjacencyListGraph class.
#include "adjacency_list_graph.hpp"

#include "doctest.hpp"
#include "graph_adt_test.hpp"

TEST_CASE_TEMPLATE_INVOKE(test_id, AdjacencyListGraph);

#endif