// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf // clear structures // statement // doublesz
#include <bits/stdc++.h>
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define REP(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// for 64 bit
//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){

	cout << rng() << endl;
	
	vector<int> perm(10);
	iota(perm.begin(),perm.end(),0);
	shuffle(perm.begin(),perm.end(),rng);
	for(int x : perm) cout << x << " "; cout << endl;
	 
	// measure time
	auto cl_start = clock();
	while( (clock()-cl_start)<=2.7*CLOCKS_PER_SEC ){	
		// do sth 
	}
	return 0;
}
