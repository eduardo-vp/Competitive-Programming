#include <bits/stdc++.h>

#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define N 10000
#define INF INT_MAX
using namespace std;

int l,u,r;
int but[10];
int dist[10100];
queue<int> cola;

void bfs(){
  while(!cola.empty()){
    int u = cola.front(); cola.pop();
    for(int i = 0; i < r; i++){
      int v = (u + but[i])%N;
      if(dist[v] == INF){
        dist[v] = dist[u]+1;
        cola.push(v);
      }
    }
  }
}

int main(){

  int tc = 1;
  while(cin >> l >> u >> r){
    if(l == 0 and u == 0 and r == 0) break;
    for(int i = 0; i < r; i++) 
      scanf("%d",but+i);
    for(int i = 0; i < N; i++) dist[i] = INF;
    cola.push(l); dist[l] = 0;
    bfs();
    printf("Case %d: ",tc++);
    if(dist[u] == INF) printf("Permanently Locked\n");
    else printf("%d\n",dist[u]);
  }

  return 0;
}