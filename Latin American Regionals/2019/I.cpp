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
#define N 2048
#define MOD 1000000007
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int vist[N];
ll dp[N];
vector<int> adj[N];

ll dfs(int u){
	if(vist[u]) return dp[u];
	vist[u] = 1;
	if(!sz(adj[u])) return dp[u] = 1;
	ll ans = 0;
	for(int v : adj[u]){
		ans += dfs(v);
		ans %= MOD;
	}
	return dp[u] = ans;
}

int main(){

	fastio;
	int n,l;
	cin >> n >> l;
	for(int i = 1; i <= l; ++i){
		int k,x;
		cin >> k;
		for(int j = 0; j < k; ++j){
			cin >> x;
			adj[i].pb(x);
		}
	}

	fill(vist,0);
	ll ans1 = dfs(1);
	int ans2 = 0;
	for(int i = l+1; i <= n; ++i)
		ans2 += vist[i];
	
	cout << ans1 << " " << ans2 << endl;

	return 0;
}

