#include "brute_force.hpp"
#include <cstdio>

BruteForce::BruteForce(Graph G):G_(G){};

void BruteForce::ChangeGraph(Graph G){
  G_=G;
};

double BruteForce::Solve(){
  std::vector<int> value(G_.n_+G_.m_);
  double ans=1e9;
  std::function<void(int,int)> dfs = [this,&value,&ans,&dfs](int p,double sum){
    if(p==G_.n_+G_.m_){
      if(sum==493){
        for(int i=0;i<G_.n_+G_.m_;i++){
          printf("%d ",value[i]);
          if(i<G_.n_){
            printf(" %lf\n",G_.node_[i].F_(value[i]));
          }
          else{
            printf(" %lf\n",G_.edge_[i-G_.n_].F_(value[i]));
          }
        }
      }
      ans=std::min(ans,sum);
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
        value[p]=i;
        dfs(p+1,sum+=G_.edge_[pos].F_(i));
      }
    }
  };
  dfs(0,0);
  return ans;
}