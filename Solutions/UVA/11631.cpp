#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int m,n,x,y,z,cost,p[200100],rk[200100];
vector<iii> edges;

int findSet(int x){ return (p[x] == x) ? x : (findSet(p[x])); }
bool isSameSet(int x, int y){ return findSet(x) == findSet(y); }
void unionSet(int i, int j){
  int x = findSet(i), y = findSet(j);
  if(rk[x] > rk[y]) p[y] = x;
  else{
    p[x] = y;
    if(rk[x] == rk[y]) rk[y]++;
  }
}

void kruskal(){
  sort(edges.begin(),edges.end());
  for(int i = 0; i < n; i++){
    int x = edges[i].second.first, y = edges[i].second.second;
    if(!isSameSet(x,y)){
      unionSet(x,y);
      cost -= edges[i].first;
    }
  }
}

int main(){

  while(cin >> m >> n){
    if(m == 0 and n == 0) break;
    cost = 0;
    for(int i = 0; i < n; i++){
      cin >> x >> y >> z;
      cost += z;
      edges.pb(mp(z,ii(x,y)));
    }
    for(int i = 0; i < m; i++) p[i] = i;
    fill(rk,0);
    kruskal();
    cout << cost << endl;
    edges.clear();
  }

  return 0;
}