#include"cost_scaling.hpp"
#include<vector>
#include<iostream>
using namespace std;

vector<InputEdge> e;
int main(){
  freopen("/home/yuhan/notuse/a.txt","w",stdout);
  int n,m,s,t;
  cin>>n>>m>>s>>t;
  for(int i=1;i<=m;i++)
  {
    int u,v,w,c;
    cin>>u>>v>>w>>c;
    u--;
    v--;
    e.push_back({u,v,0,w});
  }
  e.push_back({t-1,s-1,-1,0x3f3f3f3f});
  double ans=MinCost(n,e);
  cout<<ans<<endl;
  return 0;
}