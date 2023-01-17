#include "brute_force.hpp"

BruteForce::BruteForce(Graph G):G_(G){};

int BruteForce::Solve(){
  int length=G_.n_+G_.m_;
  std::vector<int> value(G_.n_);
  int ans=__INT_MAX__;
  std::function<void(int,int)> dfs = [this,length,&value,&ans,&dfs](int p,int sum){
    if(p==length){
      ans=std::max(ans,sum);
      return;
    }
    if(p<G_.n_){
      for(int i=G_.node_[p+1].l_;i<=G_.node_[p+1].r_;i++){
        value[p]=i;
        dfs(p+1,sum+G_.node_[p+1].F_(i));
      }
    }
    else{
      int pos=p-G_.n_;
      for(int i=G_.edge_[pos].l_;i<=G_.edge_[pos].r_;i++){
        if(value[G_.edge_[pos].u_-1]-value[G_.edge_[pos].v_-1]>i){
          continue;
        }
        dfs(p+1,sum+=G_.edge_[pos].F_(i));
      }
    }
  };
  return ans;
}