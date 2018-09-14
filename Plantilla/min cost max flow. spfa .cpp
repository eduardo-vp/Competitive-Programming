//min cost max flow spfa mode, comentar el fill(funcion del arreglo)
 
#define  INF  1000000000000000
struct edge { 
  ll dest,origcap, cap, cost, rev;
  edge(){}
  edge(ll dest, ll origcap, ll cap, ll cost, ll rev) :
  dest(dest), origcap(origcap), cap(cap), cost(cost), rev(rev){} 
};
struct MinCostMaxFlow {
  vector<edge> adj[N];
  ll dis[N], queued[N];
  ll cost,source, target, iter,cap;
  edge* pre[N];
  MinCostMaxFlow (){}
  inline void AddEdge(ll from, ll to, ll cap, ll cost) {
    adj[from].pb(edge {to, cap, cap, cost, sz(adj[to])});
    adj[to].pb(edge {from,0, 0, -cost, sz(adj[from])- 1});
  }
  inline bool spfa() {
    FER(i,0,N) queued[i] = 0;
    fill(dis, dis + N, INF);
    queue<ll> q;
    pre[source] =0, pre[target] = 0, dis[source] = 0;
    q.emplace(source), queued[source] = 1;
    while (!q.empty()) {
      ll x = q.front(), d = dis[x];
      q.pop(), queued[x] = 0;
      for (auto &e : adj[x]) {
        ll y = e.dest, w = d + e.cost;
        if (e.cap < 1 || dis[y] <= w) continue;
        dis[y] = w, pre[y] = &e;
        if(!queued[y]) q.push(y), queued[y] = 1;
      }
    }
    edge* e = pre[target];
    if (!e) return 0;
    while (e) {
      edge& rev = adj[e->dest][e->rev];
      e->cap -= cap, rev.cap += cap;
      cost += cap * e->cost, e = pre[rev.dest];
    }
    return 1;
  }
  inline ii GetMaxFlow(ll S, ll T) {
    cap = 1, source = S, target = T, cost = 0;
    while(spfa()) {}
    ll totflow = 0;
    for(auto e: adj[source]) totflow += (e.origcap - e.cap);
    return {totflow, cost};
  }
};
