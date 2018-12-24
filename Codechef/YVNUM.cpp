// dile a la jardinera que traigo flores
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 100020
#define MOD 1000000007
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int n;
ll pot[N], suf[N], pref[N];

ll f(char c){ return c - '0'; }

inline ll sum(ll a, ll b){ 
	ll x = a + b;
	if(x > MOD) x -= MOD;
	return x;
}

ll binpow(ll x, ll p){
	ll ans = 1;
	while(p){
		if(p&1LL) ans = (ans*x)%MOD;
		x = (x*x)%MOD;
		p >>= 1;
	}
	return ans;
}

void build(){
	pot[0] = 1;
	for(int i = 1; i < N; ++i) pot[i] = (pot[i-1]*10)%MOD;
}


ll base(string &cad){
	ll ans = (f(cad[n-1])*pot[n-1])%MOD;
	for(int i = n-2; i >= 0; --i)
		ans = sum(ans,(f(cad[i])*pot[n-2-i])%MOD);
	return ans;
}

ll getPref(ll x, ll b){
	ll ans = suf[n-x];
	// exp = n*b + n-b;
	ans = (ans * binpow(pot[n],b)) % MOD;
	ans = (ans * pot[n-b-1]) % MOD;
	return ans;
}

ll getSuf(ll x, ll b){
	if(!x) return 0;
	ll ans = pref[x-1];
	// exp = b*n - (n-x) ;
	ans = (ans * binpow(pot[n],b-1))%MOD;
	ans = (ans * pot[x]) % MOD;
	return ans;
}

ll go(string &cad){
	n = sz(cad);
	pref[0] = (pot[n-1]*f(cad[0]))%MOD;
	for(int i = 1; i < n; ++i)
		pref[i] = (pref[i-1] + (f(cad[i])*pot[n-1-i])%MOD)%MOD;
	suf[n-1] = f(cad[n-1]);
	for(int i = n-2; i >= 0; --i)
		suf[i] = (suf[i+1] + (f(cad[i])*pot[n-1-i])%MOD)%MOD;

	ll ans = base(cad);
	for(int i = n; i > 1; --i){
		ans = sum(ans,getPref(i,i-1));
		ans = sum(ans,getSuf(n-i,i-1));
	}
	return ans;
}

int main(){

	fastio;
	build();
	int tc;
	string cad;
	cin >> tc;
	while(tc--){
		cin >> cad;
		cout << go(cad) << endl;
	}

	return 0;
}
