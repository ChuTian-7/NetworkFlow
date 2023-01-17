#include "brute_force.hpp"

BruteForce::BruteForce(Graph G):G_(G){};

int BruteForce::Solve(){
  int length=G_.n_+G_.edge_.size();
  std::vector<int> value(G_.n_);
  int ans=__INT_MAX__;
  std::function<void(int,int)> dfs = [this,length,&value,&ans](int p,int sum){
    if(p==length){
      ans=std::max(ans,sum);
      return;
    }
    if(p<G_.n_){
      for(int i=G_.node_[p+1].l_;i<=G_.node_[p+1].r_;i++){
        
      }
    }
  };
}