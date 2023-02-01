// #include "cost_scaling.hpp"
// #include <math.h>
// #include <vector>
// #include <stack>
// using namespace std;
// #define int long long
// double epsilon, flow;

// struct InputEdge {
//   int u, v, cost, capilty;
// };

// struct Edge {
//   int u, v, cost, capilty;
// };

// vector<int> p;  // potential
// vector<int> head;
// vector<Edge> edge;
// vector<int> init_ioflow;  // 入-出
// int N, len;
// int total_cost = 0;

// int CostPi(int u,Edge e){
//   return e.cost-p[u]+p[e.v];
// }

// void Refine() {
//   for(int u=0;u<N;u++){
//     for(int i=head[u];i!=-1;i=edge[i].u){
//       if(CostPi(u,edge[i])<0){
//         edge[i^1].capilty+=edge[i].capilty;
//         edge[i].capilty=0;
//       }
//     }
//   }
//   vector<int> ioflow(init_ioflow);
//   vector<bool> vis(N,0);
//   for(auto e:edge){
//     ioflow[e.v]-=e.capilty;
//   }
//   stack<int> st;
//   for(int u=0;u<N;u++){
//     if(ioflow[u]>0){
//       st.push(u);
//       vis[u]=1;
//     }
//   }
  
//   auto Push = [&](int u,int x,int flow){
//     edge[x].capilty-=flow;
//     edge[x^1].capilty+=flow;
//     ioflow[u]-=flow;
//   };

//   auto Relabel = [&] (int u){
//     p[u]+=epsilon/2;
//   };

//   auto Modify = [&](int u){
//     for(int i=head[u];i!=-1;i=edge[i].v){
//       if(edge[i].cost>0){
//         Push(u,i,min(edge[i].cost,ioflow[u]));
//       }
//       if(ioflow[u]==0){
//         return;
//       }
//     }
//     Relabel(u);
//   };

//   while(!st.empty()){
//     Modify(st.top());
//     st.pop();
//   }
// }

// void AddEdge(int u, int v, int c, int p) {
//   edge[++len] = {head[u], v, c, p};
//   head[u] = len;
// }

// void Init(vector<InputEdge> arc) {
//   epsilon = 0;
//   flow = 0;
//   head.resize(N, -1);
//   //ioflow.resize(N, 0);
//   len = -1;
//   for (auto e : arc) {
//     epsilon = max(epsilon, e.cost * 1.0);
//     total_cost += e.capilty * e.cost;
//     init_ioflow[e.u] += e.capilty;
//     //ioflow[e.v] -= e.capilty;
//     AddEdge(e.u, e.v, e.cost, e.capilty);
//     AddEdge(e.v, e.u, -e.cost, 0);
//   }
//   p.resize(N, 0);
// }

// double MinCost(int n, vector<InputEdge> arc) {
//   N=n;
//   Init(arc);
//   while (epsilon >= 1.0 / n) {
//     Refine();
//     epsilon = epsilon / 2;
//   }
//   for(auto e:edge){
//     total_cost-=e.capilty*e.cost;
//   }
//   return total_cost/2;
// }
// #undef int