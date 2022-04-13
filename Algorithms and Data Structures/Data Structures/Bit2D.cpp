
template<typename T>
struct Fenwick2D {
  int n, m;
  vector< vector<T> > bit;
 
  Fenwick2D(int n, int m): n(n), m(m) {
    bit.resize(n);
    for (int i = 0; i < n; ++i) {
      bit[i].resize(m);
    }
  }
 
  inline void modify(int i, int j, T v) {
    int x = i;
    while (x < n) {
      int y = j;
      while (y < m) {
        bit[x][y] += v;
        y |= (y + 1);
      }
      x |= (x + 1);
    }
  }
 
  inline T get(int i, int j) {
    T v{};
    int x = i;
    while (x >= 0) {
      int y = j;
      while (y >= 0) {
        v += bit[x][y];
        y = (y & (y + 1)) - 1;
      }
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};
