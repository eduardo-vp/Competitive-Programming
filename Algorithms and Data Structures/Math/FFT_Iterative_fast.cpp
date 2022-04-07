
typedef long long ll;
typedef complex<long double> base; 
const long double PIII = 3.1415926535897932384626433832795028841971693993751;
 
void fft (vector<base> &a, bool invert) {
  int n = (int) a.size();
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1)
      j -= bit;
    j += bit;
    if (i < j)
      swap (a[i], a[j]);
  }
 
  for (int len = 2; len <= n; len <<= 1) {
    long double ang = 2 * PIII / len * (invert ? -1 : 1);
    base wlen (cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      base w(1);
      for (int j = 0; j < len / 2; ++j) {
        base u = a[i + j],  v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if (invert)
    for (int i = 0; i < n; ++i)
      a[i] /= n;
}
 
vector<ll> multiply(vector<ll> x, vector<ll> y) {
  if(x.size() == 0 || y.size() == 0) return {};
  vector<base> fa, fb;
  size_t n = 1;
  while (n < max (x.size(), y.size()))  n <<= 1;
  n <<= 1;
  fa.resize(n),  fb.resize(n);
  for (int i = 0; i < (int)x.size(); i++) {
    fa[i] = x[i];
  }
  for (int i = 0; i < (int)y.size(); i++) {
    fb[i] = y[i];
  }
 
  fft (fa, false),  fft (fb, false);
  for (size_t i = 0; i < n; ++i)
    fa[i] *= fb[i];
  fft (fa, true);
 
  vector<ll> res(x.size() + y.size() - 1);
  for (int i=0; i<(int)res.size(); ++i)
    res[i] = (ll) (fa[i].real() + 0.5); 
  return res;
}
