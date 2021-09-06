// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#include <sys/resource.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 100100
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

stack<int> pila;
vector<ii> st;
int tc,n,m,color[N],par[N],pai[N];
int cnt,num[N],low[N];
bool allow[N], flag[N];
vector<int> adj[N];
vector< vector<ii> > bcc;

bool dfs(int u, int p = -1){
  for(int v : adj[u]) if(v != p and allow[v]){
    if(color[v] == -1){
      color[v] = 1 - color[u];
      if(dfs(v,u)) return true;
    }
    if(color[u] == color[v]) return true;
  }
  return false;
}

bool bipartite(vector<int> &vec){
  for(int i = 0; i < sz(vec); ++i){ 
    int v = vec[i];
    allow[v] = true, color[v] = -1;
  }
  color[vec[0]] = 0;
  bool resp = dfs(vec[0]);
  for(int i = 0; i < sz(vec); ++i){
    int v = vec[i];
    allow[v] = false;
  }
  return !resp;
}

void tarjan(int u, bool root = 0){
  num[u] = low[u] = cnt++;
  int child = 0;
  for(int v : adj[u]) if(v != par[u]){
    if(num[v] == -1){
      child++, par[v] = u;
      st.push_back(ii(u,v));
      tarjan(v);
      low[u] = min(low[u],low[v]);
      if((root && child > 1) || (!root && num[u] <= low[v])){
        vector<ii> tmp;
        while(st.back() != ii(u,v)) tmp.pb(st.back()), st.pop_back();
        tmp.pb(st.back()), st.pop_back();
        bcc.pb(tmp);
      }
    }else if(num[v] < num[u]){
      low[u] = min(low[u],num[v]);
      st.pb(ii(u,v));
    }
  }
}

int main(){

  const rlim_t kStackSize = 64L * 1024L * 1024L;
  struct rlimit rl;
  int result;
  result = getrlimit(RLIMIT_STACK,&rl);
  if(result == 0){
    if(rl.rlim_cur < kStackSize){
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK,&rl);
      if(result != 0){
        fprintf(stderr,"setrlimit returned result = %d\n",result);
      }
    }
  }

  fastio;
  int TC,a,b;
  cin >> TC;
  fill(allow,0);
  for(tc = 1; tc <= TC; ++tc){
    cin >> n >> m;
    bcc.clear();
    FER(i,1,n+1) adj[i].clear();

    FER(i,0,m){
      cin >> a >> b;
      adj[a].pb(b);
      adj[b].pb(a);
    }
    cnt = 0;
    fill(flag,0);
    FER(i,1,n+1) par[i] = num[i] = low[i] = -1;

    for(int i = 1; i <= n; ++i) if(num[i] == -1){ 
      tarjan(i,1);
      if(sz(st)) bcc.pb(st);
      st.clear();
    }

    // check if bcc's are bipartite
    for(vector<ii> &v : bcc){
      vector<int> vec;
      for(ii p : v) vec.pb(p.ff), vec.pb(p.ss);
      sort(vec.begin(),vec.end());
      vec.erase(unique(vec.begin(),vec.end()),vec.end());
      if(!bipartite(vec)){
        for(int x : vec) flag[x] = 1;
      }
    }

    int ans = 0;
    FER(i,1,n+1) ans += flag[i];
    cout << ans << endl;
  }

  return 0;
}
