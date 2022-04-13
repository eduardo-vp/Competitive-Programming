
template<typename T>
struct Fenwick {
  int n;
  vector<T> bit;

  Fenwick(int n): n(n) {
    bit.resize(n);
  }

  void modify(int x, T v) {
    while (x < n) {
      bit[x] += v;
      x = x | (x + 1);
    }
  }

  // query in [0, x]
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += bit[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }

  // query in [l, r]
  T get(int l, int r) {
    return get(r) - get(l - 1);
  }
};

