// based on : https://codeforces.com/contest/1383/submission/87919031

template<typename T, T mod>
struct Tint{
	T val;
	Tint(): val(0){}
	Tint(long long x){ x %= mod; if(x < 0) x += mod; val = x; }
	// basic operations
	Tint& operator += (Tint oth){ val += oth.val; if(val >= mod) val -= mod; return *this; }
	Tint& operator -= (Tint oth){ val -= oth.val; if(val < 0) val += mod; return *this; }
	Tint& operator *= (Tint oth){ val = (long long)(val) * oth.val % mod; return *this; }
	Tint operator + (Tint oth) const{ return Tint(*this) += oth; }
	Tint operator - (Tint oth) const{ return Tint(*this) -= oth; }
	Tint operator * (Tint oth) const{ return Tint(*this) *= oth; }
	// if division is required
	Tint& operator /= (Tint oth){ return *this *= oth.inverse(); }
	Tint operator / (Tint oth) const{ return Tint(*this) /= oth; }
	Tint inverse() const{
		long long a = val, b = mod, u = 1, v = 0;
		while(b){
			long long t = a/b;
			a -= t*b; swap(a,b);
			u -= t*v; swap(u,v);
		}
		if(u < 0) u += mod;
		return u;
	}
	// relational operators
	bool operator < (Tint oth) const{ return val < oth.val; }
	bool operator > (Tint oth) const{ return val > oth.val; }
	bool operator <= (Tint oth) const{ return val <= oth.val; }
	bool operator >= (Tint oth) const{ return val >= oth.val; }
	bool operator == (Tint oth) const{ return val == oth.val; }
	bool operator != (Tint oth) const{ return val != oth.val; }
};

// usage
const ll MOD = 1e9+7;
using Mint = Tint<int,MOD>;
