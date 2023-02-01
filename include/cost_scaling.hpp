#include <math.h>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define int long long
double epsilon, flow;

struct InputEdge {
  int u, v, cost, capilty;
};

struct Edge {
  int u, v, cost, capilty, forward;
};

vector<int> p;  // potential
vector<int> head;
vector<Edge> edge;
vector<int> init_ioflow;  // 入-出
int N, len;
int total_cost = 0;

int CostPi(int u, Edge e) {
  return e.cost - p[u] + p[e.v];
}

void Refine() {
  for (int u = 0; u < N; u++) {
    for (int i = head[u]; i != -1; i = edge[i].u) {
      if (CostPi(u, edge[i]) < 0) {
        edge[i ^ 1].capilty += edge[i].capilty;
        edge[i].capilty = 0;
      }
    }
  }
  vector<int> ioflow(init_ioflow);
  vector<bool> vis(N, 0);
  // for (auto e : edge) {
  //   ioflow[e.v] -= e.capilty;
  // }
  for(int u=0;u<N;u++){
    for(int i=head[u];i!=-1;i=edge[i].u){
      if(edge[i].forward){
        cout<<u<<" "<<edge[i].v<<" "<<edge[i].cost<<" "<<edge[i].capilty<<endl;
        ioflow[u]+=edge[i].capilty;
        ioflow[edge[i].v]-=edge[i].capilty;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    cout << ioflow[i] << " ";
  }
  cout << endl;
  stack<int> st;
  for (int u = 0; u < N; u++) {
    if (ioflow[u] > 0) {
      st.push(u);
      vis[u] = 1;
    }
  }

  auto Push = [&](int u, int x, int flow) {
    edge[x].capilty -= flow;
    edge[x ^ 1].capilty += flow;
    ioflow[u] -= flow;
    ioflow[edge[x].v] += flow;
    cout << u << " " << edge[x].v << " " << flow << " " << ioflow[edge[x].v]
         << endl;
    if (ioflow[edge[x].v] > 0 && vis[edge[x].v] == 0) {
      st.push(edge[x].v);
      vis[edge[x].v] = 1;
    }
  };

  auto Relabel = [&](int u) { p[u] += epsilon / 2; };

  auto Modify = [&](int u) {
    for (int i = head[u]; i != -1; i = edge[i].u) {
      if (edge[i].capilty > 0) {
        Push(u, i, min(edge[i].capilty, ioflow[u]));
      }
      cout << edge[i].capilty << " " << ioflow[u] << endl;
      if (ioflow[u] == 0) {
        return;
      }
    }
    Relabel(u);
  };

  while (!st.empty()) {
    int u = st.top();
    st.pop();
    vis[u] = 0;
    cout << "assimble:" << u << endl;
    Modify(u);
  }
}
void AddEdge(int u, int v, int c, int p, int f) {
  edge.push_back({head[u], v, c, p, f});
  len++;
  head[u] = len;
}

void Init(vector<InputEdge> arc) {
  epsilon = 1;
  flow = 0;
  head.resize(N, -1);
  init_ioflow.resize(N);
  // ioflow.resize(N, 0);
  len = -1;
  for (auto e : arc) {
    cout<<e.u<<" "<<e.v<<" "<<e.cost<<" "<<e.capilty<<endl;
    epsilon = max(epsilon, e.cost * 1.0);
    total_cost += e.capilty * e.cost;
    //init_ioflow[e.u] += e.capilty;
    // ioflow[e.v] -= e.capilty;
    AddEdge(e.u, e.v, e.cost, e.capilty, 1);
    AddEdge(e.v, e.u, -e.cost, 0, 0);
  }
  p.resize(N, 0);
}

double MinCost(int n, vector<InputEdge> arc) {
  N = n;
  Init(arc);
  while (epsilon * N >= 1.0) {
    cout << epsilon << endl;
    Refine();
    epsilon = epsilon / 2;
  }
  total_cost = 0;
  for (auto e : edge) {
    // if (e.cost <= 0)
    //   continue;
    // cout << e.capilty << " " << e.cost << endl;
    total_cost += e.capilty * e.cost;
  }
  return total_cost / 2;
}
#undef int