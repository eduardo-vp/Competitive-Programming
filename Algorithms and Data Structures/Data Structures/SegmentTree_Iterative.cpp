
struct STree{
  int n;
  vector<int> t;
  STree(int n): n(n), t(2 * n + 5) {}
  void build(vector<int> &vec) {
    assert(vec.size() == n);
    for (int i = 0; i < n; ++i) {
      t[n + i] = vec[i];
    }
    for (int i = n - 1; i > 0; --i) {
      t[i] = max(t[i << 1], t[i << 1 | 1]);
    }
  }
  int query(int l, int r) {
    int ans = INT_MIN;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = max(ans, t[l++]);
      if (r & 1) ans = max(ans, t[--r]);
    }
    return ans;
  }
  void update(int p, int v) {
    for (t[p += n] = v; p >>= 1; ) {
      t[p] = max(t[p << 1], t[p << 1 | 1]);
    }
  }
};
