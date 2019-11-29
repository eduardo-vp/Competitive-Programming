
// Gracias MarcosK

struct node{
	int mx,mn,sum;
	node(){}
	node(int mx, int mn, int sum):mx(mx),mn(mn),sum(sum){}
	node merge(node x){
		node ans;
		ans.sum=sum+x.sum;
		ans.mx=max(mx,sum+x.mx);
		ans.mn=min(mn,sum+x.mn);
		return ans;
	}
};
 
node NEUT(0,1e9,-1e9);

struct STree { // segment tree for min over integers
	vector<node> st;int n;
	STree(int n): st(4*n+5,node(0,0,0)), n(n) {}
	void upd(int k, int s, int e, int p, int v){
		if(s+1==e){st[k]=node(v,v,v);return;}
		int m=(s+e)/2;
		if(p<m)upd(2*k,s,m,p,v);
		else upd(2*k+1,m,e,p,v);
		st[k]=st[2*k].merge(st[2*k+1]);
	}
	node query(int k, int s, int e, int a, int b){
		if(s>=b||e<=a)return NEUT;
		if(s>=a&&e<=b)return st[k];
		int m=(s+e)/2;
		return query(2*k,s,m,a,b).merge(query(2*k+1,m,e,a,b));
	}
	void upd(int p, int v){upd(1,0,n,p,v);}
	node query(int a, int b){return query(1,0,n,a,b);}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(i,v);rmq.query(s,e);
