#include "brute_force.hpp"
#include "graph.hpp"
#include "deque"
#include "testlib.h"
#include "gen.h"
#include "functional"
#include <cstdio>
#include <cmath>

std::deque<Graph> G={
  Graph(1,0,
  {
    {0,0,[](int x){return 0;}},
    {-2,2,[](int x){return 2*x*x-3*x;}},
  },
  {}),
  Graph(2,1,
	{
		{0,  0, [](int) { return 0; }},
		{-2, 2, [](int x) { return -x; }},
		{-2, 2, [](int x) { return +x; }},
	},
	{
		{-4, 4, [](int x) { return (x - 3) * (x - 3); }, 1, 2}
	}),
  Graph(
    2,1,
		{
			{0,  0, [](int) { return 0; }},
			{-2, 2, [](int x) { return -x; }},
			{-2, 2, [](int x) { return +x; }},
		},
		{
			{-4, 4, [](int x) { return (x + 3) * (x + 3); }, 1, 2}
		}
  ),
  Graph(
    2,1,
		{
			{0,  0, [](int) { return 0; }},
			{-4, 4, [](int x) { return x*x; }},
			{-5, 3, [](int x) { return 3*x*x+4*x; }},
		},
		{
			{-3, 3, [](int x) { return 2*x*x-3*x; }, 1, 2}
		}
  ),
  Graph(
    2,1,
		{
			{0,  0, [](int) { return 0; }},
			{-4, 4, [](int x) { return x*x; }},
			{-5, 3, [](int x) { return 3*x*x+4*x; }},
		},
		{
			{-10, -7, [](int x) { return 2*x*x-3*x; }, 1, 2}
		}
  ),
  Graph(
    2,1,
		{
			{0,  0, [](int) { return 0; }},
			{-4, 4, [](int x) { return x*x; }},
			{-5, 3, [](int x) { return 3*x*x+4*x; }},
		},
		{
			{-100, -90, [](int x) { return 2*x*x-3*x; }, 1, 2}
		}
  )
};

std::function<double(int)> RandF(){
  int a=rnd.next(0,10);
  int b=rnd.next(-10,10);
  int c=rnd.next(-10,10);
  return [a,b,c](int x){return a*x*x+b*x+c;};
}

void TinyGen(int n,int ml,int x=0){
  int m=rnd.next(n-1,ml);
  GraphGenerator::Graph graph;
  rnd.setSeed(x);
  graph.SetNode(n);
  graph.SetSide(m);
  graph.SetConnect(true);
  graph.SetMultiplyEdge(true);
  graph.GenGraph();
  std::vector<std::pair<int,int>> e=graph.GetEdge();
  Graph nxt;
  nxt.n_=n;
  nxt.m_=m;
  nxt.node_.resize(n+1);
  nxt.edge_.resize(m);
  for(int i=1;i<=n;i++){
    nxt.node_[i].l_=rnd.next(-2,2);
    nxt.node_[i].r_=rnd.next(-2,2);
    if(nxt.node_[i].l_>nxt.node_[i].r_){
      std::swap(nxt.node_[i].l_,nxt.node_[i].r_);
    }
    nxt.node_[i].F_=RandF();
  }
  for(int i=0;i<m;i++){
    std::map<std::pair<int,int>,std::pair<int,int>> mp;
    nxt.edge_[i].l_=rnd.next(-2,8);
    nxt.edge_[i].r_=rnd.next(-2,8);
    if(nxt.edge_[i].l_>nxt.edge_[i].r_){
      std::swap(nxt.edge_[i].l_,nxt.edge_[i].r_);
    }
    nxt.edge_[i].F_=RandF();
    if(mp.count(e[i])==0){
      e[i]=mp[e[i]];
    }
    else{
      mp[e[i]]=e[i];
      mp[std::make_pair(e[i].second,e[i].first)]=e[i];
    }
    nxt.edge_[i].u_=e[i].first;
    nxt.edge_[i].v_=e[i].first;
  }
  G.push_back(nxt);
  return;
}

int main(){
  BruteForce bf;
  int cas=0;
  for(int i=1;i<=3;i++){
    TinyGen(4,8,i);
  }
  for(auto g:G){
    cas++;
    bf.ChangeGraph(g);
    double answer=bf.Solve();
    if(answer==1e9){
      answer=nan("");
    }
    printf("Test %d: answer = %lf\n",cas,answer);
  }
  return 0;
}