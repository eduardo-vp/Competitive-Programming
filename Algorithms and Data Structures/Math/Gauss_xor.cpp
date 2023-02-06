
// Based on https://codeforces.com/blog/entry/68953

/* vectors are represented by bitmasks of length D (usually 30 for ai <= 1e9)
 * let f(x) be the lowest bit in the binary representation of x, the key idea here is to maintain a basis of vectors with *different* f() values
 * so if f(x) represents either the lowest or highest bit in the binary representation of x works
 * usually when the maximum possible xor is required, we want f(x) to be the highest bit. Thus, while inserting the vectors, insert from bit (d - 1) to bit 0
 *
 * basis[i]: keeps the mask of the vector whose f() value is i
 * sz: current size of the basis
 */

struct Gauss {
  int basis[D];
  int sz;
 
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
