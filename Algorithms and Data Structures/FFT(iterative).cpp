// Gracias Yefrigg

const double PI = acos(-1);

typedef double T;
struct Cpx {
  T real, image;
  Cpx( T real, T image ): real(real), image(image) {}
  Cpx( T real ): real(real), image(0) {}
  Cpx() { real = 0; image = 0; }
};
Cpx operator +( const Cpx &c1, const Cpx &c2) {
  return Cpx(c1.real + c2.real, c1.image + c2.image );
}
Cpx operator -( const Cpx &c1, const Cpx &c2) {
  return Cpx(c1.real - c2.real, c1.image - c2.image );
}
Cpx operator *( const Cpx &c1, const Cpx &c2) {
  return Cpx(c1.real*c2.real - c1.image*c2.image, c1.image*c2.real + c1.real*c2.image);
}
 
int rev(int id, int len) {
  int ret = 0;
  for (int i = 0; (1 << i) < len; i++) {
    ret <<= 1;
    if (id & (1 << i)) ret |= 1;
  }
  return ret;
}
 
vector<Cpx> FFT(vector<Cpx>& a, int dir) {
  int len = sz(a);
  vector<Cpx> A(len);
  for (int i = 0; i < len; i++) A[rev(i, len)] = a[i];
  for (int s = 1; (1 << s) <= len; s++) {
    int m = (1 << s);
    Cpx wm = Cpx(cos(dir * 2 * PI / m), sin(dir * 2 * PI / m ));
    for (int k = 0; k < len; k += m) {
      Cpx w = Cpx(1, 0);
      for (int j = 0; j < (m >> 1); j++) {
        Cpx t = w * A[k + j + (m >> 1)];
        Cpx u = A[k + j];
        A[k + j] = u + t;
        A[k + j + (m >> 1)] = u - t;
        w = w * wm;
      }
    }
  }
  if (dir == -1) for (int i = 0; i < len; i++) {
    A[i].real /= len;
    A[i].image /= len;
  }
  return A;
}
 
vector<int> multiply(vector<int> &pol1, vector<int> &pol2) {
  int n = 1;
  while (n < sz(pol1) + sz(pol2)) n *= 2;
  vector<Cpx> a(n), b(n);
  for (int i = 0; i < sz(pol1); i++) a[i] = Cpx(pol1[i], 0);
  for (int i = 0; i < sz(pol2); i++) b[i] = Cpx(pol2[i], 0);
  vector<Cpx> a_fft = FFT(a, 1);
  vector<Cpx> b_fft = FFT(b, 1);
  vector<Cpx> c_fft(n);
  for (int i = 0; i < n; i++) c_fft[i] = a_fft[i] * b_fft[i];
  vector<Cpx> c = FFT(c_fft, -1);
  vector<int> ans(n);
  for (int i = 0; i < sz(ans); i++) ans[i] = ll(round(c[i].real));
  return ans;
}
