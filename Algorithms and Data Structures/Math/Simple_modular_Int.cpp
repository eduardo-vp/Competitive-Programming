
template<typename T, T mod>
struct Modular{
  T val;
  Modular(): val(0) {}
  Modular(long long x) { x %= mod; if(x < 0) x += mod; val = x; }
  // basic operations
  Modular& operator += (Modular oth) { val += oth.val; if(val >= mod) val -= mod; return *this; }
  Modular& operator -= (Modular oth) { val -= oth.val; if(val < 0) val += mod; return *this; }
  Modular& operator *= (Modular oth) { val = (long long)(val) * oth.val % mod; return *this; }
  Modular operator + (Modular oth) const { return Modular(*this) += oth; }
  Modular operator - (Modular oth) const { return Modular(*this) -= oth; }
  Modular operator * (Modular oth) const { return Modular(*this) *= oth; }
  // if division is required
  Modular& operator /= (Modular oth) { return *this *= oth.inverse(); }
  Modular operator / (Modular oth) const { return Modular(*this) /= oth; }
  Modular inverse() const {
    long long a = val, b = mod, u = 1, v = 0;
    while (b) {
      long long t = a/b;
      a -= t*b; swap(a,b);
      u -= t*v; swap(u,v);
    }
    if(u < 0) u += mod;
    return u;
  }
  // relational operators
  bool operator == (Modular oth) const{ return val == oth.val; }
  bool operator != (Modular oth) const{ return val != oth.val; }
};
