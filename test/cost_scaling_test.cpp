#include <math.h>
#include <iostream>
#include <stack>
#include <vector>
#include <assert.h>
using namespace std;
#define int long long
double epsilon, flow;

struct InputEdge {
  int u, v, cost, capacity,lower,upper,id;
};

struct Edge {
  int u, v, cost, capacity,total,id;
};

vector<int> f;

vector<double> p;  // potential
vector<int> head;

vector<Edge> edge;
vector<int> init_ioflow;  //flow
int N, len;
int total_cost = 0;

double CostPi(int u, Edge e) {
  return e.cost - p[u] + p[e.v];
}

bool Refine() {
  vector<int> ti(N,0);
  for (int u = 0; u < N; u++) {
    for (int i = head[u]; i != -1; i = edge[i].u) {
      if (CostPi(u, edge[i]) < 0) {
        edge[i ^ 1].capacity += edge[i].capacity;
        edge[i].capacity = 0;
      }
    }
  }
  vector<int> ioflow(init_ioflow);
  vector<bool> vis(N, 0);
  // cout<<"edges:"<<endl;
  // for(int u=0;u<N;u++){
  //   for(int i=head[u];i!=-1;i=edge[i].u){
  //     auto e=edge[i];
  //     cout<<u<<" "<<e.v<<" "<<e.cost<<" "<<e.capacity<<endl;
  //   }
  // }
  // cout<<"potential:"<<endl;
  // for(auto x:p){
  //   cout<<x<<" ";
  // }
  // cout<<endl;
  // cout<<"ioflow:"<<endl;
  // for (int i = 0; i < N; i++) {
  //   cout << ioflow[i] << " ";
  // }
  // cout << endl;  
  for (auto e : edge) {
    ioflow[e.v] -= e.capacity;
  }
  stack<int> st;
  for (int u = 0; u < N; u++) {
    if (ioflow[u] > 0) {
      st.push(u);
      vis[u] = 1;
    }
  }

  auto Push = [&](int u, int x, int flow) {
    edge[x].capacity -= flow;
    edge[x ^ 1].capacity += flow;
    ioflow[u] -= flow;
    ioflow[edge[x].v] += flow;
    //cout << u << " " << edge[x].v << " " << flow << " " << ioflow[edge[x].v]<< endl;
    if (ioflow[edge[x].v] > 0 && vis[edge[x].v] == 0) {
      st.push(edge[x].v);
      vis[edge[x].v] = 1;
    }
    for(int i=0;i<edge.size();i++){
      //cout<<i<<" "<<(i^1)<<" "<<edge[i].capacity<<" "<<edge[i^1].capacity<<" "<<edge[i].total<<endl;
      assert(edge[i].capacity+edge[i^1].capacity==edge[i].total);
    }
  };

  auto Relabel = [&](int u) { 
    p[u] += epsilon / 2; 
    //cout<<"p:"<<u<<" "<<p[u]<<endl;  
  };

  auto Modify = [&](int u) {
    assert(ioflow[u]>0);
    for (int i = head[u]; i != -1; i = edge[i].u) {
      double w=CostPi(u,edge[i]);
      //cout<<"costpi:"<<u<<" "<<w<<endl;
      //if (-epsilon/2<=w && w<0) {
      if(w<0){
        Push(u, i, min(edge[i].capacity, ioflow[u]));
        // if(ioflow[u]>0){
        //   st.push(u);
        //   vis[u]=1;
        // }
        // return;
      }
      //cout << edge[i].capacity << " " << ioflow[u] << endl;
      if (ioflow[u] == 0) {
        return;
      }
    }
    assert(ioflow[u]>0);
    Relabel(u);
    st.push(u);
    vis[u]=1;
  };
  while (!st.empty()) {
    int u = st.top();
    st.pop();
    vis[u] = 0;
    ti[u]++;
    if(ti[u]>N){
      return false;
    }
    //cout << "assimble:" << u << endl;
    Modify(u);
  }
  return true;
}
void AddEdge(int u, int v, int c, int p,int tot,int id) {
  edge.push_back({head[u], v, c, p, tot,id});
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
    //cout<<e.u<<" "<<e.v<<" "<<e.cost<<" "<<e.capacity<<endl;
    epsilon = max(epsilon, e.cost * 1.0);
    total_cost += e.capacity * e.cost;
    init_ioflow[e.v] += e.upper;
    init_ioflow[e.u] += -e.lower;
    // ioflow[e.v] -= e.capacity;
    AddEdge(e.u, e.v, e.cost, e.capacity,e.capacity,-1);
    AddEdge(e.v, e.u, -e.cost, 0,e.capacity,e.id);
  }
  p.resize(N, 0);
  // cout<<"init_flow:"<<endl;
  // for(auto x:init_ioflow){
  //   cout<<x<<" ";
  // }
  // cout<<endl;
  // for(int i=0;i<edge.size();i++){
  //   assert(-edge[i].cost==edge[i^1].cost);
  // }
  // cout<<"edges:"<<endl;
  // for(auto e:edge){
  //   cout<<e.u<<" "<<e.v<<" "<<e.cost<<" "<<e.capacity<<endl;
  // }
}

pair<bool,int> MinCost(int n, vector<InputEdge> arc) {
  N = n;
  Init(arc);
  while (epsilon * N >= 1.0) {
    //cout << epsilon << endl;
    if(Refine()==false){
      return {false,0};
    }
    epsilon = epsilon / 2;
  }
  //total_cost = 0;
  //cout<<(int)total_cost<<endl;
  for (auto e : edge) {
    // if (e.cost <= 0)
    //   continue;
    // cout << e.capacity << " " << e.cost << endl;
    total_cost -= e.capacity * e.cost;
  }
  return {true,-total_cost / 2};
}
vector<InputEdge> e;
signed main(){
  int n,m,s,t;
  scanf("%lld%lld",&n,&m);
  f.resize(m);
  for(int i=1;i<=m;i++)
  {
    int u,v,l,r,c,w;
    scanf("%lld%lld%lld%lld",&u,&v,&l,&r);
    u--;
    v--;
    e.push_back({u,v,0,r-l,l,r,i-1});
    f[i-1]=l;
  }
  //e.push_back({t-1,s-1,-1,(int)1e18});
  auto [yn,ans]=MinCost(n,e);
  if(yn==false){
    cout<<"NO\n";
  }
  else{
    cout<<"YES\n";
    for(auto e:edge){
      if(e.id!=-1){
        f[e.id]+=e.capacity;
      }    
    }
    for(auto x:f){
      cout<<x<<"\n";
    }
  }
  return 0;
}
#undef int

