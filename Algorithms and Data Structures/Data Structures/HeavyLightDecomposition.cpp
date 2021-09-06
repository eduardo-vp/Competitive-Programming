const int N = 1e5+20;
vector<int> adj[N]; // graph

struct HeavyLight{
  STree st; // supports build, query [l,r) and update in position
  int gid,p[N],tsz[N],id[N],rt[N];
  int dfs_sz(int u, int pai = -1){
    p[u] = pai;
    tsz[u] = 1;
    for(int &v : adj[u]) if(v != pai){
      tsz[u] += dfs_sz(v,u);
      if(tsz[v] > tsz[adj[u][0]] || adj[u][0] == pai) swap(v,adj[u][0]);
    }
    return tsz[u];
  }
  void dfs_hld(int u){
    id[u] = gid++;
    for(int v : adj[u]) if(v != p[u]){
      rt[v] = (v == adj[u][0] ? rt[u] : v);
      dfs_hld(v);
    }
  }
  void modify(int u, int val){
    int idx = id[u];
    st.update(idx,val);
  }
  int query(int u, int v){
    int ans = 0; // identity
    while(rt[u] != rt[v]){
      if(id[u] > id[v]) swap(u,v);
      ans = max(ans,st.query(id[rt[v]],id[v]+1)); // check carefully
      v = p[rt[v]];
    }
    int a = id[u], b = id[v];
    if(a > b) swap(a,b);
    ans = max(ans,st.query(a,b+1)); // here as well
    return ans;
  }
  void init(int n, int root){
    gid = 0;
    dfs_sz(root);
    rt[root] = root;
    dfs_hld(root);
    st.build(n);
  }
};
