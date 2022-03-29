
/* Chordal graph: graph in which all cycles of four or more vertices have a chord, which is an edge that is not part of the cycle
but connects two vertices of the cycle. Equivalently, every induced cycle in the graph should have exactly three vertices

A perfect elimination ordering in a graph is an ordering of the vertices of the graph such that, 
for each vertex v, v and the neighbors of v that occur after v in the order form a clique. 
A graph is chordal if and only if it has a perfect elimination ordering.
*/

// Call is_chordal(n) to check if it's a chordal graph
// Array pos[N] has the Perfect elimination order if true

struct Chordal{
  vector<int> adj[N], a[N];
  int qu[N], pos[N], l[N], r[N], c[N];
  bool is_chordal(int n) {
    iota(qu, qu+n, 0);
    iota(pos, pos+n, 0);
    memset(l, 0, 4*n);
    r[0]=n-1;
    memset(c, 0, 4*n);
    for(int i = n-1; i >= 0; --i) {
      int u = qu[i];
      --r[l[i]];
      vector<array<int, 2>> z;
      for(int v : adj[u]) {
        if(pos[v] > i) continue;
        int lc = l[pos[v]];
        z.push_back({r[lc]-c[lc]++, r[lc]});
      }
      for(int v : adj[u]) {
        if(pos[v] > i) continue;
        int np = r[l[pos[v]]]--;
        pos[qu[np]] = pos[v];
        swap(qu[pos[v]], qu[np]);
        l[np] = np-(--c[l[pos[v]]]);
        pos[v] = np;
      }
      for(array<int, 2> a : z)
        r[a[0]] = a[1];
      int w = -1;
      for(int v : adj[u])
        if(pos[v]>i && (w<0 || pos[v]<pos[w]))
          w=v;
      if(w >= 0)
        a[w].push_back(u);
    }
    for(int i = 0; i < n; ++i) {
      for(int j : adj[i])
        c[j]=1;
      for(int j : a[i])
        for(int k : adj[j])
          if(pos[k]>pos[i] && !c[k])
            return 0;
      for(int j : adj[i])
        c[j]=0;
    }
    return 1;
  }
};
