#pragma once

#include "graph.hpp"

class  BruteForce
{
  private:
    Graph G_;
  public:
    BruteForce(){};
    BruteForce(Graph G);
    void ChangeGraph(Graph G);
    double Solve();
};