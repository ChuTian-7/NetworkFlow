#include "problem.hpp"
#include <cstdio>
#include<iostream>
using namespace std;

Problem::Problem(Graph G) {
  // 2 7a
  U = 0;
  M = 1e18;  // sufficiently large number
  n = G.n_ + 1;
  for (int i = 1; i <= G.n_; i++) {
    auto e = G.node_[i];
    edge.push_back({e.l_, e.r_, e.F_, i, 0});
  }
  for (auto e : G.edge_) {
    std::function<double(int)> E;
    // 1 assumption 3
    E = [e](int x) {
      int l = x, r = e.r_;
      while (l < r) {
        int lmid = l + (r - l) / 3;
        int rmid = r - (r - l) / 3;
        if (e.F_(lmid) <= e.F_(rmid)) {
          r = rmid - 1;
        } else {
          l = lmid + 1;
        }
      }
      double minval = std::min(e.F_(l), e.F_(r));
      return minval;
    };
    edge.push_back({e.l_, e.r_, E, e.u_, e.v_});
  }
  for (auto e : edge) {
    U = std::max(e.r_ - e.l_, U);
  }
}
