
// Gracias El vasito

struct CD {  // or typedef complex<double> CD; (but 4x slower)
	double r,i;
	CD(double r = 0, double i = 0) : r(r), i(i){}
	double real() const{ return r; }
	void operator /= (const int c){ r/=c; i/=c; }
};

CD operator*(const CD& a, const CD& b){ 
	return CD( a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}
CD operator+(const CD& a, const CD& b){
	return CD(a.r + b.r, a.i + b.i);
}
CD operator-(const CD& a, const CD& b){
	return CD(a.r - b.r, a.i - b.i);
}
const double pi = acos(-1.0); // FFT
CD cp1[MAXN+9],cp2[MAXN+9];  // MAXN must be power of 2 !!
int R[MAXN+9];
//CD root(int n, bool inv){ // NTT
//	ll r = pm(RT,(MOD-1)/n); // pm: modular exponentiation
//	return CD(inv ? pm(r,MOD-2) : r);
//}
void dft(CD* a, int n, bool inv){
	REP(i,0,n) if(R[i] < i) swap(a[R[i]],a[i]);
	for(int m = 2; m <= n; m *= 2){
		double z = 2*pi/m*(inv?-1:1); // FFT
		CD wi = CD(cos(z),sin(z)); // FFT
		// CD wi=root(m,inv); // NTT
		for(int j = 0; j < n;j += m){
			CD w(1);
			for(int k = j,k2 = j+m/2; k2 < j+m; k++, k2++){
				CD u = a[k];
				CD v = a[k2]*w;
				a[k] = u+v;
				a[k2] = u-v;
				w = w*wi;
			}
		}
	}
	if(inv) REP(i,0,n) a[i]/=n; // FFT
	//if(inv){ // NTT
	//	CD z(pm(n,MOD-2)); // pm: modular exponentiation
	//	REP(i,0,n) a[i] = a[i]*z;
	//}
}
vector<int> multiply(vector<int>& p1, vector<int>& p2){
	int n = sz(p1) + sz(p2) +1;
	int m = 1, cnt = 0;
	while(m <= n) m += m, cnt++;
	REP(i,0,m){ R[i] = 0; REP(j,0,cnt) R[i] = (R[i]<<1) | ((i>>j)&1); }
	REP(i,0,m) cp1[i] = 0, cp2[i] = 0;
	REP(i,0,sz(p1)) cp1[i] = p1[i];
	REP(i,0,sz(p2)) cp2[i] = p2[i];
	dft(cp1,m,false); dft(cp2,m,false);
	REP(i,0,m) cp1[i] = cp1[i] * cp2[i];
	dft(cp1,m,true);
	vector<int> res;
	n -= 2;
	REP(i,0,n) res.pb((ll)floor(cp1[i].real()+0.5)); // change for NTT
	return res;
}
