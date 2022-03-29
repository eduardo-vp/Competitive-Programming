
vector<int> adj[N];

struct CentroidDecomposition{
  int n;
  int cpar[N], tsz[N];
  int dfs(int u, int p) {
    tsz[u] = 1;
    for(int v : adj[u]) if(v != p and cpar[v] == -1){
      tsz[u] += dfs(v, u);
    }
    return tsz[u];
  }
  
  void decomp(int u, int p, int sb, int prevc){
    for(int v : adj[u]) if(v != p and cpar[v] == -1 and 2 * tsz[v] > sb) {
      decomp(v, u, sb, prevc);
      return;
    }
    cpar[u] = prevc; // careful if prevc == -2
    for(int v : adj[u]) if(cpar[v] == -1) {
      dfs(v, u);
      decomp(v, u, tsz[v], u);
    }
  }
  
  void init(int _n){
    n = _n;
    dfs(1, -1);
    memset(cpar, -1, sizeof(cpar));
    decomp(1, -1, tsz[1], -2);
  }
};

