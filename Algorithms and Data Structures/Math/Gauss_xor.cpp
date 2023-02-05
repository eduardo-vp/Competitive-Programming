
// Based on https://codeforces.com/blog/entry/68953

struct Gauss {
  // vectors are represented by bitmasks of length D (usually 30 for ai <= 1e9)
  int basis[D]; // basis[i] keeps the mask of the vector whose f value is i
  int sz; // current size of the basis
 
  void insert(int mask) {
    for (int i = d - 1; i >= 0; --i) {
      if (((mask >> i) & 1) == 0) continue;
      if (!basis[i]) {
        basis[i] = mask;
        sz++;
        return;
      }
      mask ^= basis[i];
    }
  }
 
  // to get the maximum xor among any subset of the inserted values
  // the order in which we iterate the bits in insert() and getmax() should be from highest to lowest bit 
  int get_max() {
    int ans = 0;
    for (int i = d - 1; i >= 0; --i) {
      if (!basis[i] || ((ans >> i) & 1)) continue;
      ans ^= basis[i];
    }
    return ans;
  }
 
  // merge this basis with another basis
  void operator += (Gauss g) {
    for (int i = d - 1; i >= 0; --i) {
      if (!g.basis[i]) continue;
      insert(g.basis[i]);
    }
  }
};
