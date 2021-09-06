#include <bits/stdc++.h>

#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;

/*NETWORK FLOW PROBLEM*/

int m,w,flow,maxflow,s,t;
int res[105][105];
int visited[105], p[105];

void augment(int x, int minEdge){
  if(x == 1) flow = minEdge;
  else if(p[x] != -1){
    augment(p[x],min(minEdge,res[p[x]][x]));
    res[p[x]][x] -= flow;
    res[x][p[x]] += flow; 
  }
}

int main(){

  while(cin >> m >> w){
    if(m == 0 and w == 0) break;
    int a,b,c;
    fill(res,0);
    t = (m-1)*2;
    for(int i = 0; i < m-2; i++){
      cin >> a >> b;
      int v = (a-1)*2;
      res[v][v+1] = b;
      res[v+1][v] = b;
    }
    for(int i = 0; i < w; i++){
      cin >> a >> b >> c;
      int u = (a-1)*2, v = (b-1)*2;
      res[u+1][v] = c;
      res[v+1][u] = c;
    }
    maxflow = 0;
    while(1){
      flow = 0;
      queue<int> q; q.push(1);
      fill(visited,0);
      fill(p,-1);
      while(!q.empty()){
        int u = q.front(); q.pop();
        if(u == t) break;
        for(int i = 1; i < 100; i++)
          if(!visited[i] and res[u][i] > 0)
            visited[i] = 1, q.push(i), p[i] = u; 
      }
      augment(t,INT_MAX);
      if(flow == 0) break;
      maxflow += flow;
    }
    cout << maxflow << endl;
  }

  return 0;
}