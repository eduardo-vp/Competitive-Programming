// cities to vapori-
// corner cases // int vs ll // cin vs scanf // clear structures // statement // doublesz
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define REP(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
const int N = 1 << 17, LGMAX = 18;

// Gracias El vasito
const int NEUT = 0;
struct STree{ // persistent segment tree for sum over integers
  int n,rt;
  vector<int> st,left,right;
  STree(int n) : st(1,NEUT), left(1,0), right(1,0), n(n), rt(0){}
  int comb(int a, int b){
    return a + b;
  }
  int new_node(int v, int l = 0, int r = 0){
    int ks = sz(st);
    st.pb(v); left.pb(l); right.pb(r);
    return ks;
  }
  int update(int k, int s, int e, int p, int v){
    int ks = new_node(st[k],left[k],right[k]);
    if(s+1 == e){ st[ks] += v; return ks; }
    int m = (s+e)/2, ps;
    if(p < m) ps = update(left[ks],s,m,p,v), left[ks] = ps;
    else ps = update(right[ks],m,e,p,v), right[ks] = ps;
    st[ks] = comb(st[left[ks]],st[right[ks]]);
    return ks;
  }
  int query(int u, int v, int lca, int plca, int s, int e, int k){
    if(s+1 == e) return s;
    int m = (s+e)/2;
    int count = st[left[u]] + st[left[v]] - st[left[lca]] - st[left[plca]];
    if(count >= k) return query(left[u],left[v],left[lca],left[plca],s,m,k);
    return query(right[u],right[v],right[lca],right[plca],m,e,k-count);
  }
  int update(int k, int p, int v){ return rt = update(k,0,n,p,v); }
}; 
// usage: STree rmq(n); root = rmq.init(x); new_root = rmq.update(root,i,v); rmq.query(root,s,e);

int root[N];
STree st(N);
vector<int> adj[N];
map<int,int> comp;
int value[N],uncomp[N],P[N][LGMAX],dep[N];

void dfs(int u, int p = -1, int d = 0){
  dep[u] = d;
  P[u][0] = p;
  for(int i = 1; i < LGMAX && P[u][i-1] != -1; ++i){
    P[u][i] = P[P[u][i-1]][i-1];
  }
  root[u] = st.update((p == -1) ? 0 : root[p], comp[value[u]], 1);
  for(int i = 0; i < sz(adj[u]); ++i) if(adj[u][i] != p){
    dfs(adj[u][i],u,d+1);
  }
}

int __lca(int a, int b){
  if(dep[a] < dep[b]) swap(a,b);
  for(int i = LGMAX-1; i >= 0; --i){
    if(dep[a] - (1 << i) >= dep[b])
      a = P[a][i];
  }
  if(a == b) return a;
  for(int i = LGMAX-1; i >= 0; --i){
    if(P[a][i] != P[b][i])
      a = P[a][i], b = P[b][i];
  }
  return P[a][0];
}

int main(){

  fastio;
  int n,m;
  cin >> n >> m;
  vector<int> vec;
  for(int i = 1; i <= n; ++i){
    cin >> value[i];
    vec.pb(value[i]);
  }

  sort(vec.begin(),vec.end());
  vec.erase(unique(vec.begin(),vec.end()),vec.end());
  for(int i = 0; i < sz(vec); ++i){
    int k = sz(comp);
    comp[vec[i]] = k;
    uncomp[k] = vec[i];
    k++;
  }
  
  for(int i = 0; i < n-1; ++i){
    int a,b;
    cin >> a >> b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  
  dfs(1);
  root[0] = 0;
  while(m--){
    int u,v,k;
    cin >> u >> v >> k;
    int lca = __lca(u,v);
    int plca = (lca == 1 ? 0 : P[lca][0]);
    int ans = st.query(root[u],root[v],root[lca],root[plca],0,N,k);
    cout << uncomp[ans] << '\n';
  }

  return 0;
}
