
typedef long double ld;
typedef complex<double> cd;
 
const int mod = (119 << 23) + 1, root = 3; // = 998244353
// NTT: For p < 2^30 there is also e.g. (5 << 25, 3),
// (7 << 26, 3), (479 << 21, 3) and (483 << 21, 5).
// The last two are > 10^9.
 
const ld pi = 4 * atan((ld)1);
int size(int s){ return s > 1 ? 32 - __builtin_clz(s - 1) : 0; }
 
int sum(int a, const int &b){ if((a += b) >= mod) a -= mod; return a; }
int sub(int a, const int &b){ if((a -= b) < 0) a += mod; return a; }
int mult(int a, const int &b){ return (1LL * a * b) % mod; }
 
int binpow(long long x, long long p){
  int ans;
  for(ans = 1; p; p >>= 1){
    if(p & 1LL) ans = mult(ans, x);
    x = mult(x, x);
  }
  return ans;
}
 
void genRoots(vector<cd>& roots){ // primitive n-th roots of unity
  int n = roots.size();
  ld ang = 2 * pi / n;
  for(int i = 0; i < n; ++i)
    roots[i] = cd(cos(ang * i), sin(ang * i));
}
 
void genRoots(vector<int>& roots){
  int n = roots.size();
  int r = binpow(root, (mod - 1) / n);
  roots[0] = 1;
  for(int i = 1; i < n; ++i)
    roots[i] = mult(roots[i - 1], r);
}
 
void Fft(vector<int> &a, const vector<int>& roots, bool inv = 0){
  int n = a.size();
  // sort numbers from 0 to n-1 by reverse bit representation
  for (int i = 1, j = 0; i < n; ++i){
    int bit = n >> 1;
    for(; j & bit; bit >>= 1) j^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1)
    for (int i = 0; i < n; i += len)
      for (int j = 0; j < len/2; ++j) {
        int ind = n / len * j;
        if(inv && ind) ind = n - ind;
        // for xor conv don't multiply by roots[ind]
        int u = a[i + j], v = mult(a[i + j + len / 2], roots[ind]);
        a[i + j] = sum(u, v), a[i + j + len / 2] = sub(u, v);
      }
  if(inv){
    int i = binpow(n, mod - 2);
    for(int &x : a) x = mult(x, i);
  }
}
 
vector<int> Mult(vector<int> a, vector<int> b){
  int as = a.size(), bs = b.size();
  if(!min(as, bs)) return {};
  int s = as + bs - 1, n = 1 << size(s);
  vector<int> roots(n);
  genRoots(roots);
  a.resize(n); Fft(a, roots);
  b.resize(n); Fft(b, roots);
  for(int i = 0; i < n; ++i)
    a[i] = mult(a[i], b[i]);
  Fft(a,roots,true);
  a.resize(s);
  return a;
}
