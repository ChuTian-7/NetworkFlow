#pragma once

#include <queue>
#include <functional>

class Node{
  private:
    int l_,r_;
    std::function<double(int)> F_;
    friend class BruteForce;
  public:
    Node(){};
    Node(int l,int r,std::function<double(int)> F);
};

class Edge{
  private:
    int l_,r_;
    std::function<double(int)> F_;
    int u_,v_;
    friend class BruteForce;
  public:
    Edge(){};
    Edge(int l,int r,std::function<double(int)> F,int u,int v);
};

class Graph{
  private:
    int n_,m_;
    std::deque<Node> node_;
    std::deque<Edge> edge_;
    friend class BruteForce;
  public:
    Graph(){};
    Graph(int n,int m,std::deque<Node>node,std::deque<Edge> edge);
};