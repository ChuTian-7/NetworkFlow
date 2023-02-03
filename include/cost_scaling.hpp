#pragma once
#include <math.h>
#include <iostream>
#include <stack>
#include <vector>
#include "problem.hpp"
struct Arc {
  int l, r;
  int u, v, cost;
  double capacity;
  std::function<double(int)> F;
  int id;
};

std::vector<double> p;  // potential
std::vector<int> head;
std::vector<Arc> arc;
std::vector<double> excess;  // excess
std::vector<double> flow;
int N, len;
double M;
double epsilon;

double CostPi(int u, Arc e) {
  return e.cost - p[u] + p[e.v];
}

void AddEdge(int l,int r,int u,int v,int c,double p,std::function<double(int)> F) {
  len++;
  arc.push_back({l, r, head[u], v, c, p, F, len});
  head[u] = len;
}

double bij(Edge e, int x) {
  if (x < e.l_) {
    return -M;
  } else if (x >= e.r_) {
    return M;
  } else {
    return e.F_(x + 1) - e.F_(x);
  }
}

double bij(Arc e, int x) {
  if (x < e.l) {
    return -M;
  } else if (x >= e.r) {
    return M;
  } else {
    return e.F(x + 1) - e.F(x);
  }
}

double qij(int u, Arc e) {
  int v = e.v;
  int k = floor(p[u] - p[v]);
  if (k >= e.u) {
    return M;
  }
  if (k <= e.l) {
    return M;
  }
  return bij(e, k) - flow[e.id];
}

void PushAdmissibleEdge() {
  for (int u = 0; u < N; u++) {
    for (int i = head[u]; i != -1; i = arc[i].u) {
      double w = CostPi(u, arc[i]);
      //std::cout<<u<<" "<<arc[i].v<<" "<<w<<"\n";
      if (-epsilon < w && w < 0) {
        double q = qij(u, arc[i]);
        //std::cout<<q<<"\n";
        flow[arc[i].id] += q;
        flow[arc[i ^ 1].id] -= q;
        arc[i].capacity -= q;
        arc[i ^ 1].capacity += q;
        excess[u] -= q;
        excess[arc[i].v] += q;
      }
    }
  }
}

bool Refine() {
  PushAdmissibleEdge();
  std::stack<int> st;
  std::vector<bool> vis(N, 0);
  for (int u = 0; u < N; u++) {
    if (excess[u] > 0) {
      st.push(u);
      vis[u] = 1;
    }
  }

  auto Push = [&](int u, int x, int flow) {
    arc[x].capacity -= flow;
    arc[x ^ 1].capacity += flow;
    excess[u] -= flow;
    excess[arc[x].v] += flow;
    if (excess[arc[x].v] > 0 && vis[arc[x].v] == 0) {
      st.push(arc[x].v);
      vis[arc[x].v] = 1;
    }
  };

  auto Relabel = [&](int u) { p[u] += epsilon / 2; };

  auto Choice = [&](int u) {
    for (int i = head[u]; i != -1; i = arc[i].u) {
      double w = CostPi(u, arc[i]);
      if (-epsilon < w && w < 0) {
        Push(u, i, std::min(qij(u, arc[i]), excess[u]));
      }
      if (excess[u] == 0) {
        return;
      }
    }
    Relabel(u);
    st.push(u);
    vis[u] = 1;
  };

  while (!st.empty()) {
    int u = st.top();
    st.pop();
    vis[u] = 0;
    if (p[u] > 3 * N * epsilon) {
      return false;
    }
    Choice(u);
  }
  return true;
}

void Init(std::vector<Edge> edge) {
  arc.clear();
  head.resize(N, -1);
  excess.resize(N, 0);
  p.resize(N, 0);
  len = -1;
  for (auto e : edge) {
    for (int i = e.l_; i <= e.r_; i++) {
      //std::cout<<i<<" "<<bij(e,i)<<"\n";
      AddEdge(e.l_, e.r_, e.u_, e.v_, i, bij(e, i), e.F_);
      AddEdge(-e.u_, -e.l_, e.v_, e.u_, i, 0, e.Reverse());
    }
  }
  flow.resize(arc.size(),0);
}

double Cost(Arc e, double k) {
  int l = e.l, r = e.r;
  auto Count = [&](int x) { return e.F(x) - k * x; };
  while (l < r) {
    int lmid = l + (r - l) / 3;
    int rmid = r - (r - l) / 3;
    if (Count(lmid) <= Count(rmid)) {
      r = rmid - 1;
    } else {
      l = lmid + 1;
    }
  }
  std::cout<<l<<" "<<r;
  double minval = std::min(Count(l), Count(r));
  return minval;
}

std::pair<bool, double> MinCost(Problem p) {
  N = p.n;
  M = p.M;
  epsilon = p.U;
  Init(p.edge);
  while (epsilon * N >= 1.0) {
    if (Refine() == false) {
      return {false, 0};
    }
    epsilon = epsilon / 2;
  }
  // for (auto x : flow) {
  //   std::cout << x << " ";
  // }
  // std::cout << "\n";
  double ans = 0;
  for (auto e : arc) {
    //std::cout<<e.v<<" "<<e.cost<<" "<<e.capacity<<"\n";
    ans += Cost(e,flow[e.id]);
  }
  return {true, ans / 2};
}