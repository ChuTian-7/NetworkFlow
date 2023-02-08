#include <iostream>
#include <map>
#include "brute_force.hpp"
#include "cost_scaling.hpp"
#include "gen.h"
#include "testlib.h"
using namespace std;

struct Fun {
  int a, b, c;
};
std::vector<Fun> fun;

std::function<double(int)> RandF() {
  int a = rnd.next(0, 10);
  int b = rnd.next(-10, 10);
  int c = rnd.next(-10, 10);
  fun.push_back({a, b, c});
  return [a, b, c](int x) { return a * x * x + b * x + c; };
}

void PrintFunction(int x) {
  printf(" ( %d ) * x * x + ( %d ) * x + ( %d )", fun[x].a, fun[x].b, fun[x].c);
}

void PrintCase(Graph G) {
  printf("%d ,\n{\n", G.n_);
  printf("  {0,0,[](int){ return 0;}},\n");
  for (int i = 1; i <= G.n_; i++) {
    printf("  {%d,%d,[](int x){ return", G.node_[i].l_, G.node_[i].r_);
    PrintFunction(i - 1);
    printf(";}},\n");
  }
  printf("},\n{\n");
  for (int i = 0; i < G.m_; i++) {
    printf("  {{%d,%d,[](int x){ return", G.edge_[i].l_, G.edge_[i].r_);
    PrintFunction(i + G.n_);
    printf(";}},%d,%d},\n", G.edge_[i].u_, G.edge_[i].v_);
  }
  printf("}\n");
}

double SolveByBF(Graph g) {
  BruteForce bf;
  bf.ChangeGraph(g);
  std::vector<int> value;
  double answer = bf.Solve(value);
  for (auto x : value) {
    cout << x << " ";
  }
  cout << endl;
  if (answer == 1e9) {
    answer = nan("");
  }
  return answer;
}

Graph TinyGen(int n, int ml, int x = 0) {
  fun.clear();
  int m = rnd.next(n - 1, ml);
  Generator::Graph graph;
  rnd.setSeed(x);
  graph.SetNode(n);
  graph.SetSide(m);
  graph.SetMultiplyEdge(false);
  // graph.SetMultiplyEdge(true);
  graph.GenGraph();
  std::vector<std::pair<int, int>> e = graph.GetEdge();
  Graph nxt;
  nxt.n_ = n;
  nxt.m_ = m;
  nxt.node_.resize(n + 1);
  nxt.edge_.resize(m);
  for (int i = 1; i <= n; i++) {
    nxt.node_[i].l_ = rnd.next(-5, 5);
    nxt.node_[i].r_ = rnd.next(-5, 5);
    if (nxt.node_[i].l_ > nxt.node_[i].r_) {
      std::swap(nxt.node_[i].l_, nxt.node_[i].r_);
    }
    nxt.node_[i].F_ = RandF();
  }
  std::map<std::pair<int, int>, int> mp;
  for (int i = 0; i < m; i++) {
    nxt.edge_[i].l_ = rnd.next(-5, 5);
    nxt.edge_[i].r_ = rnd.next(-5, 5);
    if (nxt.edge_[i].l_ > nxt.edge_[i].r_) {
      std::swap(nxt.edge_[i].l_, nxt.edge_[i].r_);
    }
    nxt.edge_[i].F_ = RandF();
    if (mp[e[i]]) {
      e[i] = e[mp[e[i]] - 1];
    } else {
      mp[e[i]] = i + 1;
      mp[std::make_pair(e[i].second, e[i].first)] = i + 1;
    }
    nxt.edge_[i].u_ = e[i].first + 1;
    nxt.edge_[i].v_ = e[i].second + 1;
  }
  return nxt;
}

double bij(function<double(int)> f, int l, int r, int x) {
  double M = 1e6;
  if (x < l) {
    return -M;
  }
  if (x >= r) {
    return M;
  }
  return f(x + 1) - f(x);
}

//这儿是拆边和处理，问题应该出在这里
pair<bool, double> SolveByCS(Graph g) {
  vector<function<double(int)>> functions;
  vector<pair<int, int>> limi;
  double M = 1e6;
  int cnt = 0;
  vector<InputEdge> edge;
  for (int i = 1; i <= g.n_; i++) {
    auto e = g.node_[i];
    for (int j = e.l_; j <= e.r_; j++) {
      double w = bij(e.F_, e.l_, e.r_, j) - bij(e.F_, e.l_, e.r_, j - 1);
      assert(w >= 0);
      edge.push_back({i, 0, j, w, 0, w, cnt});
      if(w>1e5)
        edge.push_back({0, i, -j, M, 0, M, cnt + 1});
    }
    cnt += 2;
    functions.push_back(e.F_);
    limi.push_back({e.l_, e.r_});
  }
  for (auto e : g.edge_) {    
    std::function<double(int)> E;
    E = [e](int x) {
      int l = e.l_, r = e.r_;
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
      return std::max(minval,e.F_(x));
    };
    e.F_=E;
    for (int i = e.l_; i <= e.r_; i++) {
      double w = bij(e.F_, e.l_, e.r_, i) - bij(e.F_, e.l_, e.r_, i - 1);
      assert(w >= 0);
      edge.push_back({e.u_, e.v_, i, w, 0, w, cnt});
      if(w>1e5)
        edge.push_back({e.v_, e.u_, -i, M, 0, M, cnt + 1});
    }

    e.l_=g.node_[e.u_].l_-g.node_[e.v_].r_;
    functions.push_back(E);
    limi.push_back({e.l_, e.r_});
    cnt += 2;
  }
  auto [success,useless] = MinCost(g.n_ + 1, edge);
  double res =0;
  for (int i = 0; i < f.size(); i += 2) {
    int fl = (f[i] - f[i+1])/2;
    auto q = [F(functions[i / 2]), li(limi[i / 2])](int x) {
      auto Count = [&](int w) { return F(w) - x * w; };
      auto [l, r] = li;
      while (l < r) {
        int lmid = l + (r - l) / 3;
        int rmid = r - (r - l) / 3;
        if (Count(lmid) <= Count(rmid)) {
          r = rmid - 1;
        } else {
          l = lmid + 1;
        }
      }
      double minval = std::min(Count(l), Count(r));
      return minval;
    };
    cout<<fl<<" "<<q(fl)<<endl;
    res+=q(fl);
  }
  return {success,res};
}

int main(int argc, char** argv) {
  int cas = 0;
  Graph g;
  // for(int i=1;i<=2;i++){
  //   rnd.setSeed(i);
  // }
  for (int i = 1; i <= 5; i++) {
    // g=TinyGen(4,6,atoi(argv[1]));
    // g=TinyGen(3,3,i+114514);
    // g=TinyGen(3,3,i+998244353);
    g = TinyGen(2, 1, i);
    printf("Test %d:\n", i);
    printf("n = %d, m = %d\n", g.n_, g.m_);
    for (int i = 1; i <= g.n_; i++) {
      printf("node %d : l = %d , u = %d , funtion = ", i, g.node_[i].l_,
             g.node_[i].r_);
      PrintFunction(i - 1);
      puts("");
    }
    for (int i = 0; i < g.m_; i++) {
      printf("edge %d : from = %d, to = %d , l = %d , u = %d , function = ",
             i + 1, g.edge_[i].u_, g.edge_[i].v_, g.edge_[i].l_, g.edge_[i].r_);
      PrintFunction(g.n_ + i);
      puts("");
    }
    auto [success, ans] = SolveByCS(g);
    cout << success<<" "<<(long long)ans << endl;
    double res = SolveByBF(g);
    cout << res << endl;
  }
  return 0;
}
