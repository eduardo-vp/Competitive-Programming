
struct Dsu {
  int n;
  bool bipartite;
  vector<int> p, rank;
  Dsu (int n): n(n), p(2 * n), rank(2 * n) {
    bipartite = true;
    iota(p.begin(), p.end(), 0);
  }
  void clear() {
    bipartite = true;
    iota(p.begin(), p.end(), 0);
    fill(rank.begin(), rank.end(), 0);
  }
  int find(int i) {
    return (p[i] == i) ? i : (p[i] = find(p[i]));
  }
  void __join(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) swap(x, y);
    if (rank[x] == rank[y]) rank[x]++;
    p[y] = x;
  }
  void join(int x, int y) {
    __join(x, y + n);
    __join(x + n, y);
    bipartite &= (find(x) != find(x + n));
  }
  bool is_bipartite() {
    return bipartite;
  }
};
