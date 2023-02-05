
// Based on https://codeforces.com/blog/entry/68953

struct Gauss {
  // vectors are represented by bitmasks of length d
  int basis[d]; // basis[i] keeps the mask of the vector whose f value is i
  int sz = 0; // current size of the basis

  // insert another vector
  void insert(int mask) {
    for (int i = 0; i < d; ++i) {
      if (((mask >> i) & 1) == 0) continue;
      if (!basis[i]) {
        basis[i] = mask;
        sz++;
        return;
      }
      mask ^= basis[i];
    }
  }

  int get_max() {
    int ans = 0;
    for (int i = d - 1; i >= 0; --i) {
      if (!basis[i] || ((ans >> i) & 1)) continue;
      ans ^= basis[i];
    }
    return ans;
  }
};
