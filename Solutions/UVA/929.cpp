#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define INF INT_MAX
#define trace(x) cout << #x << " = " << x << endl
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int n,m;
int tab[1050][1050];
int dist[1050][1050];
priority_queue<iii, vector<iii>, greater<iii> > cola;

int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};

void solve(){

  while(!cola.empty()){
    iii t = cola.top(); cola.pop();
    int x = t.second.first, y = t.second.second;
    int d = t.first;
    if(d > dist[x][y]) continue;
    if(x == n-1 and y == m-1){
      while(!cola.empty()) cola.pop(); return;
    }
    for(int i = 0; i < 4; i++){
      int a = x + dr[i], b = y + dc[i];
      if( (a >= 0) and (a < n) and (b >= 0) and (b < m) and (d+tab[a][b]) < dist[a][b] ){
        cola.push(mp(d+tab[a][b],ii(a,b)));
        dist[a][b] = d + tab[a][b];
      }
    }
  }
}

int main(){

  int tc;
  cin >> tc;
  while(tc--){
    cin >> n >> m;
    for(int i = 0; i < n; i++) 
      for(int j = 0; j < m; j++){ 
        scanf("%d",&tab[i][j]);
        dist[i][j] = INF;
      }
    cola.push( mp(tab[0][0],ii(0,0)) );
    dist[0][0] = tab[0][0];
    solve();
    cout << dist[n-1][m-1] << endl;
  }

  return 0;
}