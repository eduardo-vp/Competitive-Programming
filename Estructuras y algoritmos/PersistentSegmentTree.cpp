
// Gracias El vasito
const int NEUT = 0;
struct STree{ // persistent segment tree for sum over integers
	int n,rt;
	vector<int> st,L,R;
	STree(int n) : st(1,NEUT), L(1,0), R(1,0), n(n), rt(0){}
	int comb(int a, int b){
		return a + b;
	}
	int new_node(int v, int l = 0, int r = 0){
		int ks = sz(st);
		st.pb(v); L.pb(l); R.pb(r);
		return ks;
	}
	int update(int k, int s, int e, int p, int v){
		int ks = new_node(st[k],L[k],R[k]);
		if(s+1 == e){ st[ks] += v; return ks; }
		int m = (s+e)/2, ps;
		if(p < m) ps = update(L[ks],s,m,p,v), L[ks] = ps;
		else ps = update(R[ks],m,e,p,v), R[ks] = ps;
		st[ks] = comb(st[L[ks]],st[R[ks]]);
		return ks;
	}
	int query(int k, int s, int e, int a, int b){
		if(e <= a || b <= s) return NEUT;
		if(a <= s && e <= b) return st[k];
		int m = (s+e)/2;
		return comb(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
	}
	int update(int k, int p, int v){ return rt = update(k,0,n,p,v); }
	int query(int k, int a, int b){ return query(k,0,n,a,b); }
}; 
// usage: STree rmq(n); root = rmq.init(x); new_root = rmq.update(root,i,v); rmq.query(root,s,e);
