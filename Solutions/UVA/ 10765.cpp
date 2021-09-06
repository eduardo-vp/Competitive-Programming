#include <bits/stdc++.h>
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;

int counter,root,childs;
vi parent,num,low,visited,artc;
vector<vi> g;
vector<ii> ans;

void tarjan(int x){
  num[x] = low[x] = counter++;
  for(int i = 0; i < int(g[x].size()); i++){
    int v = g[x][i];
    if(num[v] == -1){
      parent[v] = x;
      if(x == root) childs++;
      tarjan(v);
      if(x != root and low[v] >= num[x] and artc[x] == 0){ 
        ans.pb(ii(x,0));
        artc[x] = 1;
      }
      low[x] = min(low[x],low[v]);
    }else if(parent[x] != v) low[x] = min(low[x],num[v]);
  }
}

void dfs(int x){
  visited[x] = 1;
  for(int i = 0; i < (int)g[x].size(); i++){
    int v = g[x][i];
    if(!visited[v])
      dfs(v);
  }
}

bool cmp(ii a, ii b){
  if(a.second > b.second) return true;
  if(a.second < b.second) return false;
  if(a.first < b.first) return true;
  return false;
}

int main(){

  int n,m;
  while(cin >> n >> m){
    if(n == m and n == 0) break;
    g.assign(n,vi());
    int a,b;
    while(cin >> a >> b){
      if(a == -1 and b == -1) break;
      g[a].pb(b); g[b].pb(a);
    }
    counter = 0,childs = 0;
    parent.assign(n,0);
    num.assign(n,-1);
    low.assign(n,0);
    artc.assign(n,0);
    for(int i = 0; i < n; i++)
      if(num[i] == -1){
        root = i;
        childs = 0;
        tarjan(i);
        if(childs > 1) ans.pb(ii(i,0)),artc[i] = 1;
      }

    for(int i = 0; i < int(ans.size()); i++){
      int v = ans[i].first;
      vi aux = g[v];
      g[v].clear();
      visited.assign(n,0);
      int count = 0;
      for(int j = 0; j < n; j++)
        if(j != v and visited[j] == 0){
          dfs(j); count++;
        }
      g[v] = aux;
      ans[i].second = count;
    }
    sort(ans.begin(),ans.end(),cmp);
    visited.assign(n,0);
    for(int i = 0; i < min(m,(int)ans.size()); i++){
      visited[ans[i].first] = 1;
      cout << ans[i].first << " " << ans[i].second << endl;
    }
    int res = m - (int)ans.size();
    for(int i = 0; i < n and res > 0; i++){
      if(visited[i]) continue;
      res--;
      cout << i << " " << 1 << endl;
    }
    ans.clear();
    cout << endl;
  }


  return 0;
}