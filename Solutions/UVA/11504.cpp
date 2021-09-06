#include <bits/stdc++.h>
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1000000000
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 100100
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int n,m;
int numScc,cont,num[N],low[N],visited[N],sc[N];
stack<int> st;
vector< vector<int> > adj,inAdj;
vector<int> scc[N];

void dfs(int u){
  st.push(u);
  visited[u] = 1;
  num[u] = low[u] = ++cont;
  FOR(i,0,adj[u].size()){
    int v = adj[u][i];
    if(!num[v]){
      dfs(v);
      low[u] = min(low[u],low[v]);
    }else if(visited[v])
      low[u] = min(low[u],num[v]);
  }
  if(num[u] == low[u]){
    scc[numScc].clear();
    int v;
    do{
      v = st.top();
      st.pop();
      sc[v] = numScc;
      scc[numScc].pb(v);
      visited[v] = 0;
    }while(u != v);
    numScc++;
  }
}

int main(){

  int tc;
  cin >> tc;
  while(tc--){
    cin >> n >> m;
    adj.assign(n+1,vector<int>());
    inAdj.assign(n+1,vector<int>());
    int a,b;
    FOR(i,0,m){
      cin >> a >> b;
      adj[a].pb(b);
      inAdj[b].pb(a);
    }
    cont = numScc = 0;
    FOR(i,1,n+1) num[i] = visited[i] = 0;
    FOR(i,1,n+1){
      if(!num[i]) dfs(i);
    }

    int ans = 0;
    FOR(i,0,numScc){
      bool outScc = true;
      FOR(j,0,scc[i].size()){
        int u = scc[i][j];
        FOR(k,0,inAdj[u].size()){
          int v = inAdj[u][k];
          if(sc[v] != sc[u]){
            outScc = false;
            break;
          }
        }
        if(!outScc) break;
      }
      if(outScc) ans++;
    }
    cout << ans << endl;
  }

    return 0;
}
