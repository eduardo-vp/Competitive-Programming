#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1e9
#define fill(x,v) memset(x,v,sizeof(x))
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n,m;
int dist[1100];
vector<vii> g;
bool ncycle;

void BF(){
  for(int i = 0; i < n-1; i++)
    for(int u = 0; u < n; u++)
      for(int j = 0; j < (int)g[u].size(); j++){
        int v = g[u][j].fst, w = g[u][j].snd;
        dist[v] = min(dist[v],dist[u]+w);
      }
  for(int u = 0; u < n and !ncycle; u++){
    for(int j = 0; j < (int)g[u].size() and !ncycle; j++){
      int v = g[u][j].fst, w = g[u][j].snd;
      if(dist[u]+w < dist[v]) ncycle = true;
    }
  }
}

int main(){

  int tc;
  cin >> tc;
  while(tc--){
    cin >> n >> m;
    int x,y,z;
    g.assign(n,vii());
    for(int i = 0; i < m; i++){
      cin >> x >> y >> z;
      g[x].pb(ii(y,z));
    }
    for(int i = 0; i < n; i++) dist[i] = INF;
    dist[0] = 0;
    ncycle = false;
    BF();
    if(ncycle) cout << "possible" << endl;
    else cout << "not possible" << endl;
    g.clear();
  } 

  return 0;
}