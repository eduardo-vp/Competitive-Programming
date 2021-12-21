/* Gracias El vasito
   Dinic Max Flow
   Intrucciones de uso:
      Min cut: nodes with dist>=0 vs nodes with dist<0
      Matching MVC: left nodes with dist<0 + right nodes with dist>0
*/

typedef long long tf; // flow type
const tf inf = 2e18;

struct Dinic{
  int nodes, src, dst;
  vector<int> dist, q, work;
  struct edge { int to, rev; tf f, cap; };
  vector<vector<edge>> g;
  Dinic(int x): nodes(x), g(x), dist(x), q(x), work(x) {}
  void add_edge(int s, int t, tf cap) {
    g[s].push_back((edge){t, int(g[t].size()), 0, cap});
    g[t].push_back((edge){s, int(g[s].size()) - 1, 0, 0});
  }
  bool dinic_bfs(){
    fill(dist.begin(),dist.end(),-1);
    dist[src] = 0;
    int qt = 0; q[qt++] = src;
    for (int qh = 0;qh < qt; qh++) {
      int u = q[qh];
      for (int i = 0; i < g[u].size(); ++i) {
        edge &e = g[u][i]; int v = g[u][i].to;
        if (dist[v] < 0 && e.f < e.cap)
          dist[v] = dist[u] + 1, q[qt++] = v;
      }
    }
    return dist[dst] >= 0;
  }
  tf dinic_dfs(int u, tf f){
    if(u == dst) return f;
    for (int &i = work[u]; i < g[u].size(); ++i) {
      edge &e = g[u][i];
      if (e.cap <= e.f) continue;
      int v = e.to;
      if (dist[v] == dist[u] + 1) {
        tf df = dinic_dfs(v, min(f, e.cap - e.f));
        if (df > 0) {
          e.f += df;
          g[v][e.rev].f -= df;
          return df;
        }
      }
    }
    return 0;
  }
  tf max_flow(int _src, int _dst){
    src=_src; dst=_dst;
    tf result = 0;
    while (dinic_bfs()) {
      fill(work.begin(), work.end(), 0);
      while(tf delta = dinic_dfs(src, inf)) result += delta;
    }
    return result;
  }
};
