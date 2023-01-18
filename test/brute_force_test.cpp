#include "brute_force.hpp"
#include "graph.hpp"
#include "deque"
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

std::deque<int> ans;

int main(){
  BruteForce bf;
  int cas=0;
  for(auto g:G){
    cas++;
    bf.ChangeGraph(g);
    double ans=bf.Solve();
    if(ans==1e9){
      ans=nan("");
    }
    printf("Test %d: answer = %lf\n",cas,ans);
  }
  return 0;
}