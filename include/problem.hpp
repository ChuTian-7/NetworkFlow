#pragma once
#include"graph.hpp"
#include <vector>
#include <functional>

class Problem{
  public:
    std::vector<Edge> edge;
    int n,U;
    double M;
    Problem(Graph G){};
};