/*
  Convex Hull Trick
*/

// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 50100
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	const ll inf = 1e18;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = lower_bound(x);
		while(begin() != l) erase(begin());
		return (*l).k * x + (*l).m;
	}
};

LineContainer lc;

int n,q;
ll m[N],b[N];

int main(){

	lc.add(0,0);
	fill(m,0);
	fill(b,0);
	scanf("%d %d",&n,&q);
	ll type,tme,cyc,ns;
	while(q--){
		scanf("%lld",&type);
		if(type == 1){
			scanf("%lld %lld %lld",&tme,&cyc,&ns);
			ll c = tme, d = m[cyc]*tme + b[cyc];
			m[cyc] = ns;
			b[cyc] = d - ns*c;
			lc.add(m[cyc],b[cyc]);
		}else{
			scanf("%lld",&tme);
			printf("%lld\n",lc.query(tme));
		}
	}

	return 0;
}
