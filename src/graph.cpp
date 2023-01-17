#include "graph.hpp"

Graph::Graph(int n,std::deque<Node>node,std::deque<Edge> edge)
  :n_(n),node_(node),edge_(edge){};