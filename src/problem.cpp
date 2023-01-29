#include"problem.hpp"

Problem::Problem(Graph G){
  U=0;
  M=1e9;
  n=G.n_+1;
  for(int i=1;i<=G.n_;i++){
    auto e=G.node_[i];
    edge.push_back({e.l_,e.r_,e.F_,i,0});
  }
  for(auto e:G.edge_){
    std::function<double(int)> E;
    E = [e](int x){
      int l=e.l_,r=e.r_;
      while(l<=r){
        int lmid=l+(r-l)/3;
        int rmid=r-(r-l)/3;
        if(e.F_(lmid)<=e.F_(rmid)){
          l=lmid+1;
        }
        else{
          r=rmid-1;
        }
      }
      double minval=std::min(e.F_(l),e.F_(r));
      return std::min(minval,e.F_(x));
    };
  }
  for(auto e:edge){
    U=std::max(e.r_-e.l_,U);
  }
}