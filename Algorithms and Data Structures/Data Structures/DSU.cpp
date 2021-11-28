
struct Dsu {
  int n;
  vector<int> p;
  vector<int> sz;

  Dsu(int n) : n(n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
    sz.assign(n, 1);
  }

  inline int find(int x) {
    return (x == p[x] ? x : (p[x] = find(p[x])));
  }

  inline bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      p[x] = y;
      sz[y] += sz[x];
      sz[x] = 0;
      return true;
    }
    return false;
  }
};
