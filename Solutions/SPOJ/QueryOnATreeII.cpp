// i will show you da wae
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 10020
#define LG 15
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int n,cont;
int pai[N],sz[N],dep[N],head[N],getNode[N],id[N], t[2*N], p[N][LG];
vector<ii> adj[N];

void build(){
  for(int i = n-1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

int stquery(int l, int r){
  int ans = 0;
  for(l += n, r += n; l < r; l >>= 1, r >>= 1){
    if(l&1) ans += t[l++];
    if(r&1) ans += t[--r];
  }
  return ans;
}

int makesz(int u, int p = -1, int d = 0){
  pai[u] = p;
  dep[u] = d;
  sz[u] = 1;
  for(ii tp : adj[u]){
    int v = tp.first;
    if(v != p) sz[u] += makesz(v,u,d+1);
  }
  return sz[u];
}

void makehld(int u, int root = 0, int cost = -1){
  id[u] = cont;
  head[u] = root;
  t[cont+n] = cost;
  getNode[cont++] = u;
  int w = 0, best = -1,cc;
  for(ii tp : adj[u]){
    int v = tp.first, vcost = tp.second;
    if(v != pai[u] and sz[v] > best)
      w = v, best = sz[v], cc = vcost;
  }
  if(w) makehld(w,root,cc);
  for(ii tp : adj[u]){
    int v = tp.first, vcost = tp.second;
    if(v != pai[u] and v != w)
      makehld(v,v,vcost);
  }
}

void buildLca(){
  for(int i = 0; i < n; ++i)
    for(int j = 1; j < LG; ++j)
      p[i][j] = -1;
  for(int i = 0; i < n; ++i) p[i][0] = pai[i];
  
  for(int j = 1; 1 << j < n; ++j){
    for(int i = 0; i < n; ++i)
      if(p[i][j-1] != -1)
        p[i][j] = p[p[i][j-1]][j-1];
  }
}

int __lca(int u, int v){
  int log;
  if(dep[u] < dep[v]) swap(u,v);
  for(log = 1; 1 << log <= dep[u]; ++log); --log;
  for(int i = log; i >= 0; --i)
    if((dep[u]-(1<<i)) >= dep[v]) u = p[u][i];
  if(u == v) return u;
  for(int i = log; i >= 0; --i){
    if(p[u][i] != p[v][i])
      u = p[u][i], v = p[v][i];
  }
  return pai[u];
}

int dist(int u, int v){
  int ans = 0;
  while(u != -1){
    if(head[u] == head[v]){
      if(dep[u] > dep[v]) swap(u,v);
      ans += stquery(id[u]+1,id[v]+1);
      u = -1;
    }else{
      if(dep[head[u]] > dep[head[v]]) swap(u,v);
      ans += stquery(id[head[v]],id[v]+1);
      v = pai[head[v]];
    }
  }
  return ans;
}

int go_up(int u, int lca, int k){
  while(1){
    if(head[u] == head[lca]){
      return getNode[id[u]-k];
    }else{
      int dst = dep[u] - dep[head[u]];
      if(k <= dst) return getNode[id[u]-k];
      k -= dst+1;
      u = pai[head[u]];
    }
  }
  return 0;
}

int kth(int u, int v, int k){
  int lca = __lca(u,v);
  if(k <= (dep[u]-dep[lca])){
    return go_up(u,lca,k);
  }else{
    k -= dep[u]-dep[lca];
    return go_up(v,lca,dep[v]-dep[lca]-k);
  }
}

int main(){
    
  fastio;
  int tc;
  cin >> tc;
  while(tc--){
    cin >> n;
    FOR(i,0,n) adj[i].clear();
    int a,b,c;
    FOR(i,0,n-1){
      cin >> a >> b >> c;
      adj[a-1].pb(ii(b-1,c));
      adj[b-1].pb(ii(a-1,c));
    }
    cont = 0;
    makesz(0);
    makehld(0);
    build();
    buildLca();
    string op;
    while(cin >> op){
      if(op[0] == 'K'){
        cin >> a >> b >> c;
        cout << kth(a-1,b-1,c-1)+1 << endl;
      }else if(op[1] == 'I'){
        cin >> a >> b;
        cout << dist(a-1,b-1) << endl;
      }else break;
    }
    if(tc) cout << endl;
  }

    return 0;
}
