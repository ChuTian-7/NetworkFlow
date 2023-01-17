#include "brute_force.hpp"
#include "graph.hpp"
#include "deque"
#include <cstdio>

std::deque<Graph> G={
  Graph(1,0,
  {
    {0,0,[](int x){return 0;}},
    {-2,2,[](int x){return 2*x*x-3*x;}},
  },
  {})
};

std::deque<int> ans;

int main(){
  BruteForce bf;
  int cas=0;
  for(auto g:G){
    cas++;
    bf.ChangeGraph(g);
    double ans=bf.Solve();
    printf("Test %d: answer = %lf\n",cas,ans);
  }
  return 0;
}