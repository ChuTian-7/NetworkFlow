#pragma once
#include <utility> 
#include "graph.hpp"

std::function<double(int)> RandF(std::pair<int,int> fun_limit);

void PrintFunction(int x);

void PrintCase(Graph G);

Graph TinyGen(int n, int mlimit, bool multi_edge,std::pair<int,int> node_limit,std::pair<int,int> edge_limit,std::pair<int,int> fun_limit,int seed);
