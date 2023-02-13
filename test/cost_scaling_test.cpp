#include <iostream>
#include <optional>
#include <cmath>
#include "generator.hpp"
#include "brute_force.hpp"
#include "ProblemSolver.hpp"
#include "problem.hpp"
using namespace std;

double SolveByBF(Graph g) {
  BruteForce bf;
  bf.ChangeGraph(g);
  std::vector<int> value;
  double answer = bf.Solve(value);
  // for (auto x : value) {
  //   cout << x << " ";
  // }
  // cout << endl;
  if (answer == 1e9) {
    answer = nan("");
  }
  return answer;
}

double SolveByLY(Graph g){
  std::vector<μLimit> μs;
	std::vector<ωLimit> ωs;
  for(auto x:g.node_){
    μs.push_back({x.l_,x.r_,x.F_});
  }
  for(auto x:g.edge_){
    ωs.push_back({{x.l_,x.r_,x.F_},(size_t)x.u_,(size_t)x.v_});
  }
  ProblemSolver p(g.n_,μs,ωs);
  auto back=(p.solve());
  double res=(back.has_value()?back.value():nan(""));
  return res;
}

double SolveByCS(Graph g) {
  Problem p(g);
  double res=p.Solve();
  return res;
}

int main(int argc, char** argv) {
  int cas = 0;
  Graph g;
  for (int i = 1; i <= 1; i++) { 
    g=TinyGen(5,10,1,{-2,2},{-2,6},{-10,10},i);
    //g = TinyGen(20,100, i);
    // printf("Test %d:\n", i);
    // printf("n = %d, m = %d\n", g.n_, g.m_);
    // for (int i = 1; i <= g.n_; i++) {
    //   printf("node %d : l = %d , u = %d , funtion = ", i, g.node_[i].l_,
    //          g.node_[i].r_);
    //   PrintFunction(i - 1);
    //   puts("");
    // }
    // for (int i = 0; i < g.m_; i++) {
    //   printf("edge %d : from = %d, to = %d , l = %d , u = %d , function = ",
    //          i + 1, g.edge_[i].u_, g.edge_[i].v_, g.edge_[i].l_, g.edge_[i].r_);
    //   PrintFunction(g.n_ + i);
    //   puts("");
    // }
    //PrintCase(g);
    double ans = SolveByCS(g);
    double res = SolveByLY(g);
    //cout<<res<<endl;      
    //double bf=SolveByBF(g);
    // if(ans!=bf && !(std::isnan(ans) && std::isnan(bf))){
    //   cout<<"Error Test "<<i<<" "<<res<<" "<<ans<<" "<<bf<<endl;
    // }
    // else 
    if(ans==res || (std::isnan(ans) && std::isnan(res))){
      cout<<"Pass Test "<<i<<endl;
    }
    else{
      cout<<"NOT PASS Test "<<i<<":"<<ans<<" "<<res<<endl;

    }      
    // cout<<"Solve by brute force:"<<endl;
    // cout<<bf<<endl;
  }
  return 0;
}