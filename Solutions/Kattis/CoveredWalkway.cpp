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
#define N 1000100
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> ii;

ll n,c,x[N],dp[N];

struct Line{
	ll m,b;
	Line(ll m, ll b) : m(m),b(b){}
	ll f(ll x){ return m*x + b; }
	ld intersect(Line &l){ return ld(b - l.b)/ld(l.m - m); }
};

deque<Line> dq;

void add(int i){
	Line line(-2*x[i],x[i]*x[i]+dp[i-1]);
	while(sz(dq) >= 2 and line.intersect(dq.back()) <= dq.back().intersect(dq[sz(dq)-2]))
		dq.pop_back();
	dq.push_back(line);
}

int main(){

	scanf("%lld %lld",&n,&c);
	FER(i,1,n+1) scanf("%lld",x+i);

	dp[0] = 0;
	for(int i = 1; i <= n; ++i){
		add(i);
		while(sz(dq) >= 2 and dq[0].f(x[i]) >= dq[1].f(x[i]))
			dq.pop_front();
		dp[i] = c + x[i]*x[i] + dq[0].f(x[i]);
	}
	printf("%lld\n",dp[n]);
	return 0;
}
