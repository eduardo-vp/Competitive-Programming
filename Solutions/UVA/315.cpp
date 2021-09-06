#include <bits/stdc++.h>
#define pb push_back
#define fill(x,v) memset((x),(v),sizeof(x))
using namespace std;

typedef vector<int> vi;

int counter,num[150],low[150],parent[150],root,childs;
int points[150];
bitset<150> visited;
vi g[150];


int artpoints(int x){
  int ans = 0;
  visited[x] = true;
  num[x] = low[x] = counter++;
  for(int i = 0; i < (int)g[x].size(); i++){
    int v = g[x][i];
    if(!visited[v]){
      parent[v] = x;
      if(x == root) childs++;
      ans += artpoints(v);
      if(low[v] >= num[x] and points[x] == 0 and x != root){
        ans += 1;
        points[x] = 1;
      }
      low[x] = min(low[x],low[v]);
    }else if(v != parent[x]) 
      low[x] = min(low[x],num[v]);
  }
  if(x == root and childs > 1) ans++;
  return ans;
}

int main(){

  int n;
  while(cin >> n){
    if(n == 0) break;
    int v,x;
    string s;
    for(int i = 1; i <= n; i++) g[i].clear();
    while(cin >> v){
      if(v == 0) break;
      getline(cin,s);
      istringstream iss(s);
      while(iss >> x){
        g[v].pb(x); g[x].pb(v);
      }
    }
    fill(points,0);
    counter = childs = 0; visited.reset(); root = 1;
    cout << artpoints(1) << endl;
  }
  
  return 0;
}