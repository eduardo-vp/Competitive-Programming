
template<typename T>
struct Fenwick {
  int n;
  vector<T> bit;

  Fenwick(int n): n(n + 1) {
    bit.resize(n + 1);
  }

  // x: 0-indexed
  void update(int x, T v) {
    x++;
    while (x < n) {
      bit[x] += v;
      x += x & -x;
    }
  }

  // sum in [0, x)
  T get(int x) {
    auto v = T();
    while (x > 0) {
      v += bit[x];
      x -= x & -x;
    }
    return v;
  }
};
