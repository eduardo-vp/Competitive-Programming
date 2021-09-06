#include <bits/stdc++.h>

#define INF 1e9
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int costs[50];

vector< vector<int> > g;
map<char,int> getId;
vector<int> in;
ll visited[50],dist[50];
stack<int> topo;

void dfs(int x){
  visited[x] = 1;
  for(int i = 0; i < int(g[x].size()); i++){
    int v = g[x][i];
    if(!visited[v])
      dfs(v);
  }
  topo.push(x);
}

void toposort(){
  fill(visited,0);
  for(int i = 0; i < int(in.size()); i++)
    if(!visited[in[i]])
      dfs(in[i]);
}

ll solve(){
  ll ans = 0LL;
  while(!topo.empty()){
    int x = topo.top(); topo.pop();
    ans = max(ans,dist[x]);
    for(int i = 0; i < int(g[x].size()); i++){
      int v = g[x][i];
      dist[v] = max(dist[v],dist[x]+costs[v]);
      ans = max(ans,dist[v]);
    }
  }
  return ans;
}

int main(){

  int tc;
  cin >> tc;
  cin.ignore(); cin.ignore();
  bool spc = false;
  while(tc--){
    if(!spc) spc = true;
    else cout << endl;
    string cad;
    int cont = 0;
    g.assign(30, vector<int>() );
    fill(dist,-1);
    while(getline(cin,cad)){
      if(cad.compare("") == 0) break;
      char ver,v; int cost;
      istringstream iss(cad);
      iss >> v >> cost;
      if(getId.count(v) == 0)
        getId[v] = cont++;
      bool flag = false;
      costs[getId[v]] = cost;
      while(iss >> ver){
        flag = true;
        if(getId.count(ver) == 0)
          getId[ver] = cont++;
        g[getId[ver]].pb(getId[v]);
      }
      if(!flag)
        in.pb(getId[v]), dist[getId[v]] = cost;
    }
    toposort();
    ll ans = solve();
    cout << ans << endl;
    g.clear(); in.clear(); getId.clear();
  }

  return 0;
}