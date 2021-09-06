#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;

int c,s,q,x,y,z,p[120],rk[120],visited[120];
vector<iii> edges;
vector<vii> g;

int find(int x){ return (p[x] == x) ? x : (find(p[x])); }
bool isSameSet(int x, int y){ return find(x) == find(y); }
void unionSet(int i, int j){
  int x = find(i), y = find(j);
  if(rk[x] > rk[y]) p[y] = x;
  else{
    p[x] = y;
    if(rk[x] == rk[y]) rk[y]++;
  }
}

void kruskal(){
  sort(edges.begin(),edges.end());
  for(int i = 0; i < s; i++){
    int x = edges[i].second.first, y = edges[i].second.second;
    if(!isSameSet(x,y)){
      unionSet(x,y);
      g[x].pb(ii(y,edges[i].first)); g[y].pb(ii(x,edges[i].first));
    }
  }
}

int solve(int x, int sum){
  visited[x] = 1;
  int ans = -1;
  if(x == y) return sum; 
  for(int i = 0; i < int(g[x].size()); i++){
    int u = g[x][i].first;
    if(!visited[u])
      ans = max(ans,solve(u,max(sum,g[x][i].second)));
  }
  return ans;
}

int main(){

  int tc = 1;
  while(cin >> c >> s >> q){
    if(c == 0 and s == 0 and q == 0) break;
    if(tc > 1) cout << endl;
    for(int i = 0; i < s; i++){
      cin >> x >> y >> z;
      edges.pb(mp(z,ii(x,y)));
    }
    for(int i = 1; i <= c; i++) p[i] = i;
    fill(rk,0);
    g.assign(c+1,vii());
    kruskal();
    printf("Case #%d\n",tc++);
    for(int i = 0; i < q; i++){
      cin >> x >> y;
      fill(visited,0);
      int ans = solve(x,-1);
      if(ans != -1) cout << ans << endl;
      else cout << "no path" << endl;
    }
    edges.clear();
    g.clear();
  }

  return 0;
}