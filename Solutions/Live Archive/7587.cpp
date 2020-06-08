/* Exchange Arguments */

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
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int n;
vector<ii> vec;

bool cmp(const ii &x, const ii &y){
	bool goodA = x.ss >= x.ff;
	bool goodB = y.ss >= y.ff;
	if(goodA and !goodB) return true;
	if(goodB and !goodA) return false;
	if(goodA and goodB) return x.ff < y.ff;
	return x.ss > y.ss;
}

int main(){
 
	while(scanf("%d",&n) == 1){
		vec.resize(n);
		FER(i,0,n) scanf("%d %d",&vec[i].ff,&vec[i].ss);
		sort(vec.begin(),vec.end(),cmp);
		ll cur = 0,ans = 1e18;
		for(ii &par : vec){
			cur -= par.ff;
			ans = min(ans,cur);
			cur += par.ss;
		}
		printf("%lld\n",-ans);
	}

	return 0;
}
