#include <iostream>
using namespace std;

vector<vector<pair<int,int> > > G; // graph g[i][j] = (v,c) v : vertex c : cost
int N;//number of nodes

void Dijkstra(){
  vector<int> D(N,987654321);
  
  //start vertex
  set<pair<int,int> > Q;
  D[0] = 0;
  Q.insert(pair<int,int>(0,0));
  while(!Q.empty()){
    pair<int,int> top = *Q.begin();
    Q.erase(Q.begin());
    int v = top.second, d = top.first;
    
    for(int i=0;i<G[v].size();i++){
      int v2 = G[v][i].first, cost = G[v][i].second;
      if(D[v2]>D[v]+cost){
        if(D[v2]!=987654321) Q.erase(Q.find(pair<int,int>(D[v2],v2)));
        D[v2] = D[v] + cost;
        Q.insert(pair<int,int>(D[v2],v2));
      }
    }
  }
}
int main() {
  // your code goes here
  return 0;
}