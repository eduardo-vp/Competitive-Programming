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
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int main(){

	fastio;
	string cad;
	cin >> cad;
	vector<ll> vec;
	for(int i = 1, x = 4; i < sz(cad); ++i, x += 2){
		if(cad[i] != cad[i-1]){
			vec.pb(1-x);
		}
	}

	vector<ll> poly;
	poly.pb(1);
	for(ll x : vec){
		vector<ll> ans;
		ans.assign(sz(poly)+1,0);
		for(int i = 0; i < sz(poly); ++i){
			ans[i+1] += poly[i];
			ans[i] += x*poly[i];
		}
		poly = ans;
	}

	if( (poly[0] > 0 and cad[0] == 'A') or (poly[0] < 0 and cad[0] == 'H')){
		for(int i = 0; i < sz(poly); ++i)
			poly[i] = -poly[i];
	}

	cout << sz(poly)-1 << endl;
	reverse(poly.begin(),poly.end());
	for(ll x : poly) cout << x << " "; cout << endl;

	return 0;
}

