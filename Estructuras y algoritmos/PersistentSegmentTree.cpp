
// Gracias El vasito
const int NEUT = 0;
struct STree{ // persistent segment tree for sum over integers
	int n,rt;
	vector<int> st,left,right;
	STree(int n) : st(1,NEUT), n(n), rt(0){}
	int comb(int a, int b){
		return a + b;
	}
	int new_node(int v, int l = 0, int r = 0){
		int ks = sz(st);
		st.pb(v); left.pb(l); right.pb(r);
		return ks;
	}
	int update(int k, int s, int e, int p, int v){
		int ks = new_node(st[k],left[k],right[k]);
		if(s+1 == e){ st[ks] += v; return ks; }
		int m = (s+e)/2, ps;
		if(p < m) ps = update(left[ks],s,m,p,v), left[ks] = ps;
		else ps = update(right[ks],m,e,p,v), right[ks] = ps;
		st[ks] = comb(st[left[ks]],st[right[ks]]);
		return ks;
	}
	int query(int k, int s, int e, int a, int b){
		if(e <= a || b <= s) return NEUT;
		if(a <= s && e <= b) return st[k];
		int m = (s+e)/2;
		return comb(query(left[k],s,m,a,b),query(right[k],m,e,a,b));
	}
	int update(int k, int p, int v){ return rt = update(k,0,n,p,v); }
	int query(int k, int a, int b){ return query(k,0,n,a,b); }
}; 
// usage: STree rmq(n); root = rmq.init(x); new_root = rmq.update(root,i,v); rmq.query(root,s,e);
