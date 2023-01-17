#pragma once

#include <functional>

class Edge{
  private:
    int l_,r_;
    std::function<double(int)> F_;
    int u_,v_;
  public:
    Edge(){};
    Edge(int l,int r,std::function<double(int)> F,int u,int v){};
};