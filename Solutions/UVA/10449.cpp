#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1e9
#define fill(x,v) memset(x,v,sizeof(x))
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n,m;
int buss[250];
int dist[250];
int vis[250],aux[250];
vector<vii> g;

void dfs(int x){
  vis[x] = 1;
  for(int i = 0; i < (int)g[x].size(); i++)
    if(vis[g[x][i].fst] == 0)
      dfs(g[x][i].fst);
}

void dfs2(int x){
  aux[x] = 1;
  dist[x] = -1;
  for(int i = 0; i < int(g[x].size()); i++){
    if(aux[g[x][i].fst] == 0)
      dfs2(g[x][i].fst);
  }
}

void BF(){
  for(int i = 0; i < n-1; i++){
    for(int u = 1; u <= n; u++){
      for(int j = 0; j < (int)g[u].size(); j++){
        int v = g[u][j].fst, w = g[u][j].snd;
        dist[v] = min(dist[v],dist[u]+w);
      }
    }
  }
  for(int u = 1; u <= n; u++){
    for(int j = 0; j < (int)g[u].size(); j++){
      int v = g[u][j].fst, w = g[u][j].snd;
      if(dist[v] > (dist[u]+w) ){
        for(int i = 0; i <= n; i++) aux[i] = 0;
        dfs2(u);
      }
    }
  }
}



int main(){

  int tc = 1;
  while(cin >> n){
    g.assign(n+1,vii());
    for(int i = 1; i <= n; i++)
      cin >> buss[i];
    cin >> m;
    int x,y,q;
    for(int i = 0; i < m; i++){
      cin >> x >> y;
      g[x].pb(ii(y,(buss[y]-buss[x])*(buss[y]-buss[x])*(buss[y]-buss[x]) ));
    }
    for(int i = 0; i <= n; i++){
      dist[i] = INF; vis[i] = 0;
    }
    dist[1] = 0;
    BF();
    dfs(1);
    cout << "Set #" << tc++ << endl;
    cin >> q;
    for(int i = 0; i < q; i++){
      cin >> x;
      if(dist[x] < 3 or (vis[x] == 0) ) cout << "?" << endl;
      else cout << dist[x] << endl; 
    }
    g.clear();
  }

  return 0;
}