// i will show you da wae
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 10050
#define INF 1000000000
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;

int n,dtime;
int t[2*N];

void build(){
  for(int i = n-1; i > 0; --i) 
    t[i] = max(t[i<<1],t[i<<1|1]);
}

int modify(int p, int val){
  for(t[p+=n] = val; p >>= 1; )
    t[p] = max(t[p<<1],t[p<<1|1]);
}

int query(int l, int r){
  int ans = INT_MIN;
  for(l += n, r += n; l < r; l >>= 1, r >>= 1){
    if(l&1) ans = max(ans,t[l++]);
    if(r&1) ans = max(ans,t[--r]);
  }
  return ans;
}

int pai[N],sz[N],id[N],dep[N],head[N],getNode[N];
vector<iii> adj[N];

int makesz(int u,int p = -1, int d = 0){
  pai[u] = p;
  sz[u] = 1;
  dep[u] = d;
  for(iii tp : adj[u]){
    int v = tp.first.first;
    if(v != p) sz[u] += makesz(v,u,d+1);
  }
  return sz[u];
}

void makehld(int u, int root = 0, int cost = -1){
  id[u] = dtime++;
  head[u] = root;
  t[id[u]+n] = cost;
  int w = 0,best = -1,cc;
  for(iii tp : adj[u]){
    int v = tp.first.first, c = tp.first.second, ind = tp.second;
    if(v == pai[u]) continue;
    getNode[ind] = v;
    if(sz[v] > best)
      best = sz[v], w = v, cc = c;
  }
  if(w) makehld(w,root,cc);
  for(iii tp : adj[u]){
    int v = tp.first.first, c = tp.first.second;
    if(v != w and v != pai[u]) makehld(v,v,c);
  }
}

void change(int u, int val){
  modify(id[getNode[u]],val);
}

int queryhld(int u, int v){
  int ans = -1;
  //cout << "query (" << u << "," << v << ") = ";
  while(u != -1){
    if(head[u] == head[v]){
      int a = id[u], b = id[v];
      if(a > b) swap(a,b);
      ans = max(ans,query(a+1,b+1));
      u = -1;
    }else{
      if(dep[head[u]] > dep[head[v]]) swap(u,v);
              ans = max(ans,query(id[head[v]],id[v]+1));
      v = pai[head[v]];
    }
  }
  return ans;
}

int main(){
   
    fastio;
  int tc;
  cin >> tc;
  while(tc--){
    cin >> n;
    int a,b,c;
    FOR(i,0,n) adj[i].clear();
    FOR(i,0,n-1){
      cin >> a >> b >> c;
      --a; --b;
      adj[a].pb(mp(ii(b,c),i));
      adj[b].pb(mp(ii(a,c),i));
    }
    dtime = 0;
    makesz(0);
    makehld(0);
    build();
    string op;
    while(cin >> op){
      if(op.compare("DONE") == 0) break;
      cin >> a >> b;
      if(op[0] == 'Q')
        cout << queryhld(a-1,b-1) << endl;
      else change(a-1,b);
    }
  }
    
    return 0; 
}
