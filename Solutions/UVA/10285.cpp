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

int tab[120][120];
int dist[10100];
vector<vector<int> > g;
vector<int> in;
stack<int> topo;
int visited[10100];

void dfs(int x){
  visited[x] = 1;
  for(int i = 0; i < int(g[x].size()); i++)
    if(!visited[g[x][i]])
      dfs(g[x][i]);
  topo.push(x);
}

void toposort(){
  fill(visited,0);
  for(int i = 0; i < int(in.size()); i++)
    if(!visited[in[i]])
      dfs(in[i]);
}

int solve(){
  int ans = 1;
  while(!topo.empty()){
    int x = topo.top(); topo.pop();
    ans = max(ans,dist[x]);
    for(int i = 0; i < int(g[x].size()); i++){
      int v = g[x][i];
      dist[v] = max(dist[v],dist[x]+1);
      ans = max(ans,dist[v]);
    }
  }
  return ans;
}

int main(){

  int tc,row,col;
  string name;
  cin >> tc;
  while(tc--){
    cin >> name >> row >> col;
    fill(dist,INF);
    g.assign(row*col,vector<int>() );
    FOR(i,0,row) FOR(j,0,col) cin >> tab[i][j];
    FOR(i,0,row){
      FOR(j,0,col){
        int id = i*col+j;
        bool flag = true;
        if(i > 0 and tab[i-1][j] < tab[i][j]) g[id].pb((i-1)*col+j);
        if(j < col-1 and tab[i][j+1] < tab[i][j]) g[id].pb( i*col+j+1 );
        if(i < row-1 and tab[i+1][j] < tab[i][j]) g[id].pb( (i+1)*col + j );
        if(j > 0 and tab[i][j-1] < tab[i][j]) g[id].pb( i*col+j-1 );

        if(i > 0 and tab[i-1][j] > tab[i][j]) flag = false;
        if(j < col-1 and tab[i][j+1] > tab[i][j]) flag = false;
        if(i < row-1 and tab[i+1][j] > tab[i][j]) flag = false;
        if(j > 0 and tab[i][j-1] > tab[i][j]) flag = false;

        if(flag)
          in.pb(id),dist[id] = 1;
      }
    }
    toposort();
    cout << name << ": " << solve() << endl;
    g.clear(); in.clear();
  } 

  return 0;
}