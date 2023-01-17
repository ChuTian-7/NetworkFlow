#include "node.hpp"

Node::Node(int l,int r,std::function<double(int)> F)
  :l_(l),r_(r),F_(F){};