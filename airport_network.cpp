#include "airport_network.hpp"

#include <cassert>
#include <string>
#include <utility>
#include <vector>

#include "adjacency_list_graph.hpp"
#include "adjacency_matrix_graph.hpp"
#include "airport_database.hpp"
#include "graph_traversal.hpp"
#include "undirected_graph.hpp"
#include "flight_route.hpp"

AirportNetwork::AirportNetwork(const AirportDatabase& airport_database):airport_database_(airport_database),airport_graph_(airport_database_.size())
// Implement the AirportNetwork constructor.
//
// Like every constructor, this should properly set all of the private data
// members of the class. You should do as much initialization as possible in the
// initializer list, though some will need to be done in the method body.

{
  std::vector<FlightRoute> routes = airport_database_.routes();
  for(int i = 0; i < routes.size();i++)
  {
    std::string code_one_ = routes[i].code_one();
    std::string code_two_ = routes[i].code_two();
    int airport_one = airport_database_.index(code_one_);
    int airport_two = airport_database_.index(code_two_);
    Airport airport_uno = airport_database_.airport(code_one_);
    Airport airport_dos = airport_database_.airport(code_two_);
    int distance = airport_uno.distance_miles(airport_dos);
    airport_graph_.add_edge(airport_one,airport_two,distance);
  }
  
}


int AirportNetwork::num_airports() const noexcept {
  return airport_graph_.vertex_count();
}

int AirportNetwork::num_flight_routes() const noexcept {
  return airport_graph_.edge_count();
}

std::vector<std::string> AirportNetwork::at_most_one_layover(
    const std::string& code) const {
  // Implement the at_most_one_layover function.
  //
  // HINT: This will require a modicum of business logic. The graph theory
  // part of the problem should be delegated to a method call in
  // graph_traversal.
  int airport_num = airport_database_.index(code);
  std::vector<bool> result = distance_at_most_two(airport_graph_,airport_num);
  std::vector<std::string> layovers;
  for(int i = 0; i < result.size();++i)
  {
    if(result[i] == true)
    {
      std::string airport_name = airport_database_.code(i);
      layovers.push_back(airport_name);
    }
  }
  return std::vector<std::string>(layovers);
}

std::vector<int> AirportNetwork::least_distance(const std::string& code) const {
  // Implement the least_distance function.
  //
  // HINT: This will require a small amount of business logic. The graph theory
  // part of the problem should be delegated to a method call in
  // graph_traversal.
  int airport_num = airport_database_.index(code);
  std::vector<int> distance_from_airport = shortest_path(airport_graph_,airport_num);

  
  return std::vector<int>(distance_from_airport);
}