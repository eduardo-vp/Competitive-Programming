// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 200100
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int dp[N];

int main(){

	ll n,k;
	string cad;
	cin >> cad >> k;
	n = sz(cad);
	cad += cad;
	dp[sz(cad)] = 0;
	for(int i = sz(cad)-1; i >= 0; --i){
		if(cad[i] == 'P') dp[i] = dp[i+1]+1;
	}

	ll ans = n*k;
	for(int i = 0; i < n; ++i){
		if(cad[i] == 'E') continue;
		int len = min(dp[i],int(k));
		ans -= len;
	}
	cout << ans << endl;
	return 0;
}

