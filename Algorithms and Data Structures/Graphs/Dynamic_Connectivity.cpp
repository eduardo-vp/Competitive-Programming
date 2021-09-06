// Implementation used in problem https://codeforces.com/gym/100551/problem/E
// Each query is: add an edge to the graph, remove an edge of the graph or query for number of connected components
// Call go(0,number_of_queries,edges,number_of_nodes,0)
// edges -> vector<Edge> where each Edge means: an edge connecting u and v exists in [l,r)
// if(cnt[q] != cnt[q+1]) => ans[q] stores how many connected components the graph has in that query

struct Edge{
  int u,v,l,r;
  Edge(int u, int v, int l, int r) : u(u), v(v), l(l), r(r){}
};
 
vector<int> color,deg,cnt,ans,adj[N];
 
void add_edge(int u, int v){
  adj[u].pb(v);
  adj[v].pb(u);
}
 
void dfs(int u, int c){
  color[u] = c;
  for(int v : adj[u]) if(color[v] == -1) dfs(v,c);
}
 
void go(int l, int r, vector<Edge> &edges, int n, int alone){
  if(cnt[l] == cnt[r]) return;
  if(!sz(edges)){
    while(l < r) ans[l++] = n + alone;
    return;
  }
  REP(i,0,n) adj[i].clear();
  vector<Edge> other;
  for(Edge &edge : edges){
    if(edge.l <= l && r <= edge.r){
      add_edge(edge.u,edge.v);
    }else if(edge.l < r && edge.r > l){
      other.pb(edge);
    }
  }
  int comp = 0;
  REP(i,0,n) color[i] = -1, deg[i] = 0;
  REP(i,0,n) if(color[i] == -1) dfs(i,comp++);
  for(Edge &edge : other){
    edge.u = color[edge.u];
    edge.v = color[edge.v];
    if(edge.u != edge.v) deg[edge.u]++, deg[edge.v]++;
  }
  n = comp; comp = 0;
  REP(i,0,n) color[i] = comp, comp += (deg[i] > 0), alone += (deg[i] == 0);
  for(Edge &edge : other){
    edge.u = color[edge.u];
    edge.v = color[edge.v];
  }
  int m = (l+r)/2;
  go(l,m,other,comp,alone);
  go(m,r,other,comp,alone);
}
 
int main(){
 
  freopen("disconnected.in","r",stdin);
  freopen("disconnected.out","w",stdout);
 
  int n,m;
  scanf("%d %d",&n,&m);
  vector<ii> edges(m);
  vector< tuple<int,int,int> > query;
  for(int i = 0; i < m; ++i){
    scanf("%d %d",&edges[i].fst,&edges[i].snd);
    edges[i].fst--;
    edges[i].snd--;
    if(edges[i].fst > edges[i].snd) swap(edges[i].fst,edges[i].snd);
    query.pb(make_tuple(1,edges[i].fst,edges[i].snd));
  }
 
  int k,c;
  scanf("%d",&k);
  while(k--){
    scanf("%d",&c);
    vector<int> vec(c);
    for(int &id : vec) scanf("%d",&id);
    for(int &id : vec) id--;
    for(int id : vec) query.pb(make_tuple(-1,edges[id].fst,edges[id].snd));
    query.pb(make_tuple(0,0,0));
    for(int id : vec) query.pb(make_tuple(1,edges[id].fst,edges[id].snd));
  }
 
  color.resize(n+5);
  deg.resize(n+5);
  cnt.resize(sz(query)+5);
  ans.resize(sz(query)+5);
 
  map<ii,int> mp;
  vector<Edge> vec;
  int op,u,v;
  for(int q = 0; q < sz(query); ++q){
    tie(op,u,v) = query[q];
    if(op != 0){
      if(op == 1){
        mp[{u,v}] = q;
      }else{
        vec.pb(Edge(u,v,mp[{u,v}],q));
        mp.erase({u,v});
      }
    }else{
      cnt[q+1]++;
    }
    cnt[q+1] += cnt[q];
  }
 
  for(auto tup : mp){
    vec.pb(Edge(tup.fst.fst,tup.fst.snd,tup.snd,sz(query)));
  }
 
  go(0,sz(query),vec,n,0);
 
  for(int q = 0; q < sz(query); ++q){
    if(cnt[q] != cnt[q+1]){
      if(ans[q] == 1) printf("Connected\n");
      else printf("Disconnected\n");
    }
  }
 
  return 0;
}
