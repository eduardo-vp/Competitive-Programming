
const int inf = 1e9;

struct BipMatching {
  int n, m, nil;
  vector<int> match, dist;
  vector< vector<int> > adj;
  BipMatching(int n, int m): n(n), m(m) {
    nil = n + m + 2;
    match.resize(nil + 1);
    dist.resize(nil + 1);
    adj.resize(nil + 1);
  }
  void add_edge(int x, int y) {
    adj[x].push_back(y);
  }
  bool bfs() {
    queue<int> q;
    for (int i = 0; i < n; ++i) {
      if (match[i] == nil) {
        dist[i] = 0;
        q.push(i);
      } else dist[i] = inf;
    }
    dist[nil] = inf;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == nil) continue;
      for (int v: adj[u]) {
        if (dist[match[v]] == inf) {
          dist[match[v]] = dist[u] + 1;
          q.push(match[v]);
        }
      }
    }
    return dist[nil] != inf;
  }
  bool dfs(int u) {
    if (u != nil) {
      for (int v: adj[u]) {
        if (dist[match[v]] != dist[u] + 1) continue;
        if (dfs(match[v])) {
          match[v] = u;
          match[u] = v;
          return true;
        }
      }
      dist[u] = inf;
      return false;
    }
    return true;
  }
  int solve() {
    for (int i = 0; i < n + m; ++i) {
      match[i] = nil;
    }
    int matching = 0;
    while (bfs()) {
      for (int i = 0; i < n; ++i) {
        if (match[i] == nil && dfs(i)) {
          matching++;
        }
      }
    }
    return matching;
  }
};
