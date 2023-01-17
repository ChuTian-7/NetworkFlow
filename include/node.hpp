#pragma once

#include <functional>

class Node{
  private:
    int l_,r_;
    std::function<double(int)> F_;
  public:
    Node(){};
    Node(int l,int r,std::function<double(int)> F){};
};