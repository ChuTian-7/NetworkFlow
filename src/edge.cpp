#include "edge.hpp"

Edge::Edge(int l,int r,std::function<double(int)> F,int u,int v)
  :u_(u),v_(v),l_(l),r_(r),F_(F){};