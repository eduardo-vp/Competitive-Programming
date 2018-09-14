
#define INF 34084108513
// comentar N
// definir N1

struct Edge {
  ll from, to, cap, flow, index;
  Edge(ll from, ll to, ll cap, ll flow, ll index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  ll N;
  vector<vector<Edge> > G;
  vi excess, dist, active, count;
  queue<ll> Q;
  ll p[N1];

  PushRelabel(ll N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}
  inline void AddEdge(ll from, ll to, ll cap) {
    G[from].pb(Edge(from, to, cap, 0, sz(G[to])));
    if (from == to) G[from].back().index++;
    G[to].pb(Edge(to, from, 0, 0, sz(G[from]) - 1));
  }

  inline void Enqueue(ll v) { 
    if (!active[v] && excess[v] > 0) { 
      active[v] = true; Q.push(v); 
    } 
  }

  inline void Push(Edge &e) {
    ll amt = ll(min(excess[e.from], ll(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;    
    excess[e.from] -= amt;
    Enqueue(e.to);
  }
  
  inline void Gap(ll k) {
    FER(v,0,N){
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  inline void Relabel(ll v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    FER(i,0,G[v].size()) if (G[v][i].cap - G[v][i].flow > 0) dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  inline void Discharge(ll v) {
    for (ll i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1) Gap(dist[v]); 
      else Relabel(v);
    }
  }

  inline ll GetMaxFlow(ll s, ll t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    FER(i,0, G[s].size()) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }
    while (!Q.empty()) {
      ll v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }
    ll totflow = 0;
    FER(i, 0, G[s].size()) totflow += G[s][i].flow;
    return totflow;
  }
  inline void solve(){
    FER(i,0,G.size()){
      for(auto h:G[i]){
        if(h.flow>0) p[h.to]=h.from;
      }
    } 
  }
};