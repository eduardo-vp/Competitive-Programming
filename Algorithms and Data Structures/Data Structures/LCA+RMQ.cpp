// Construccion en O(n lg n) y query en O(1)
// usa la lista de adyacencia adj
// ciudado con el tamanho de LGMAX
// llamar build()
struct LCA{
  int n;
  ii node[3*N], rmq[3*N][LGMAX];
  int id[3*N],flog[3*N];
  void build(){
    n = 0;
    dfs(1);
    buildRmq();
    flog[1] = 0;
    REP(i,2,n+1) flog[i] = flog[i/2] + 1;
  }
  void dfs(int u, int p = -1, int d = 0){
    id[u] = n;
    node[n++] = {d,u};
    for(int v : adj[u]) if(v != p){
      dfs(v,u,d+1);
      node[n++] = {d,u};
    }
  }
  void buildRmq(){
    for(int i = 0; i < n; ++i)
      rmq[i][0] = node[i];
    for(int lg = 1, pw = 1; lg < LGMAX; ++lg, pw *= 2){
      for(int i = 0; i < n; ++i){
        if(i+pw < n) rmq[i][lg] = min(rmq[i][lg-1],rmq[i+pw][lg-1]);
        else rmq[i][lg] = rmq[i][lg-1];
      }
    }
  }
  int query(int u, int v){
    int i = id[u], j = id[v];
    if(i > j) swap(i,j);
    if(i == j) return rmq[i][0].second;
    int lg = flog[j-i];
    int pw = (1 << lg);
    return min(rmq[i][lg],rmq[j-pw+1][lg]).second;
  }
};
