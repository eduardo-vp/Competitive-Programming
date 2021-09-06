#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

int counter;
vector<vi> g;
vii ans;
vi visited,low,num,parent;

void tarjan(int x){
  visited[x] = 1;
  low[x] = num[x] = counter++;
  for(int i = 0; i < int(g[x].size()); i++){
    int v = g[x][i];
    if(!visited[v]){
      parent[v] = x;
      tarjan(v);
      if(low[v] > num[x]) ans.pb(ii(min(x,v),max(x,v)));
      low[x] = min(low[x],low[v]);
    }else if(parent[x] != v) low[x] = min(low[x],num[v]);
  }
}

int main(){

  int n;
  while(cin >> n){
    g.assign(n,vi());
    int v,m,x;
    char c;
    for(int i = 0; i < n; i++){
      cin >> v;
      cin >> c >> m >> c;
      for(int j = 0; j < m; j++){
        cin >> x;
        g[v].pb(x);
      }
    }
    counter = 0;
    visited.assign(n,0);
    low.assign(n,0);
    num.assign(n,0);
    parent.assign(n,0);
    for(int i = 0; i < n; i++)
      if(!visited[i])
        tarjan(i);
    cout << ans.size() << " critical links" << endl;
    sort(ans.begin(),ans.end());
    for(int i = 0; i < int(ans.size()); i++)
      cout << ans[i].fst << " - " << ans[i].snd << endl;
    ans.clear();
    cout << endl;
  }

  return 0;
}