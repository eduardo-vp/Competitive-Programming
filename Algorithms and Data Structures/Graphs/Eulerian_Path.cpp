
// Gracias El vasito
// Directed version (uncomment commented code for undirected)
struct EulerianPath {
  struct edge {
    int y;
    // list<edge>::iterator rev;
    edge(int y): y(y) {}
  };
 
  vector<int> p;
  vector< list<edge> > adj;
 
  EulerianPath(int n): adj(n) {}
 
  void add_edge(int a, int b) {
    adj[a].push_front(edge(b));
    // auto ia = adj[a].begin();
    // adj[b].push_front(edge(a));
    // auto ib = adj[b].begin();
    // ia->rev = ib; ib->rev = ia;
  }
 
  void go(int x) {
    while (adj[x].size()) {
      int y = adj[x].front().y;
      // adj[y].erase(adj[x].front().rev);
      adj[x].pop_front();
      go(y);
    }
    p.push_back(x);
  }
 
  vector<int> get_path(int x) { // get a path that begins in x
    p.clear(); // clear if get_path was previously called
    go(x);
    reverse(p.begin(), p.end());
    return p;
  }
};
 
