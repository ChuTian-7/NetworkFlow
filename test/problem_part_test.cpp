#include"graph.hpp"
#include"problem.hpp"
#include"gen.h"
#include"testlib.h"
#include<map>

struct Fun{
  int a,b,c;
};
std::vector<Fun> fun;

std::function<double(int)> RandF(){
  int a=rnd.next(0,10);
  int b=rnd.next(-10,10);
  int c=rnd.next(-10,10);
  fun.push_back({a,b,c});
  return [a,b,c](int x){return a*x*x+b*x+c;};
}

void PrintFunction(int x){
  printf(" ( %d ) * x * x + ( %d ) * x + ( %d )",fun[x].a,fun[x].b,fun[x].c);
}

void PrintCase(Graph G){
  printf("%d ,\n{\n",G.n_);
  printf("  {0,0,[](int){ return 0;}},\n");
  for(int i=1;i<=G.n_;i++){
    printf("  {%d,%d,[](int x){ return",G.node_[i].l_,G.node_[i].r_);
    PrintFunction(i-1);
    printf(";}},\n");
  }
  printf("},\n{\n");
  for(int i=0;i<G.m_;i++){
    printf("  {{%d,%d,[](int x){ return",G.edge_[i].l_,G.edge_[i].r_);
    PrintFunction(i+G.n_);
    printf(";}},%d,%d},\n",G.edge_[i].u_,G.edge_[i].v_);
  }
  printf("}\n");
}

Graph Gen(int x=0){
  fun.clear();
  int n=2;
  int m=1;
  Generator::Graph graph;
  rnd.setSeed(x);
  graph.SetNode(n);
  graph.SetSide(m);
  graph.GenGraph();
  std::vector<std::pair<int,int>> e=graph.GetEdge();
  Graph nxt;
  nxt.n_=0;
  nxt.m_=m;
  nxt.node_.resize(1);
  nxt.edge_.resize(m);
  for(int i=0;i<m;i++){   
    nxt.edge_[i].l_=rnd.next(-10,10);
    nxt.edge_[i].r_=rnd.next(-10,10);
    if(nxt.edge_[i].l_>nxt.edge_[i].r_){
      std::swap(nxt.edge_[i].l_,nxt.edge_[i].r_);
    }
    nxt.edge_[i].F_=RandF();
    nxt.edge_[i].u_=e[i].first+1;
    nxt.edge_[i].v_=e[i].second+1;
  }
  return nxt;
}

int main(){
  for(int i=1;i<=1;i++){
    Graph g=Gen(i);
    Problem p(g);
    //PrintCase(g);
    for(auto x:p.edge){
      for(int i=x.l_;i<=x.r_;i++){
        printf("%d %lf %lf\n",i,g.edge_[0].F_(i),x.F_(i));
      }
    }
  }
  return 0;
}