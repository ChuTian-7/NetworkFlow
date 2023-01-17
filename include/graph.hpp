#pragma once

#include "node.hpp"
#include "edge.hpp"
#include <queue>

class Graph{
  private:
    int n_;
    std::deque<Node> node_;
    std::deque<Edge> edge_;
    friend class BruteForce;
  public:
    Graph(){};
    Graph(int n,std::deque<Node>node,std::deque<Edge> edge){};
};