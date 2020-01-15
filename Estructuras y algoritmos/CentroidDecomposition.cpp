/* Solution to Xenia and Tree : https://codeforces.com/contest/342/problem/E */
/* Main functions: Dfs, Decomp, Init */
// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf // clear structures // statement // doublesz
#include <bits/stdc++.h>
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define REP(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 100100
#define LG 18
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

struct CentroidD{
	int n;
	int dep[N],P[N][LG],cpar[N],tsz[N],ans[N];
	vector<int> adj[N];
	
	void addEdge(int a, int b){
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	void buildLca(int u = 1, int pai = -1, int d = 0){
		dep[u] = d;
		P[u][0] = pai;
		for(int i = 1; i < LG; ++i)
			if(P[u][i-1] != -1)
				P[u][i] = P[P[u][i-1]][i-1];
		for(int v : adj[u]) if(v != pai)
			buildLca(v,u,d+1);
	}

	int __lca(int a, int b){
		if(dep[a] > dep[b]) swap(a,b);
		for(int i = LG-1; i >= 0; --i)
			if(dep[b] - (1 << i) >= dep[a])
				b = P[b][i];
		if(a == b) return a;
		for(int i = LG-1; i >= 0; --i)
			if(P[a][i] != P[b][i])
				a = P[a][i], b = P[b][i];
		return P[a][0];
	}

	int dist(int a, int b){
		return dep[a] + dep[b] - 2*dep[__lca(a,b)];
	}

	int dfs(int u, int p){
		tsz[u] = 1;
		for(int v : adj[u]) if(v != p and cpar[v] == -1){
			tsz[u] += dfs(v,u);
		}
		return tsz[u];
	}

	void decomp(int u, int p, int sb, int prevc){
		for(int v : adj[u]){
			if(v != p and cpar[v] == -1 and 2*tsz[v] > sb){
				decomp(v,u,sb,prevc);
				return;
			}
		}
		cpar[u] = prevc;
		for(int v : adj[u]){
			if(cpar[v] == -1){
				dfs(v,u);
				decomp(v,u,tsz[v],u);
			}
		}
	}

	void query(int u){
		int resp = 1e9,x = u;
		while(u != -2){
			resp = min(resp,ans[u] + dist(u,x));
			u = cpar[u];
		}
		cout << resp << endl;
	}

	void update(int u){
		int x = u;
		while(u != -2){
			ans[u] = min(ans[u],dist(u,x));
			u = cpar[u];
		}
	}

	void init(int _n){
		n = _n;
		fill(P,-1); fill(cpar,-1);
		for(int i = 1; i <= n; ++i)
			ans[i] = 1e9;
		buildLca();
		dfs(1,-1);
		decomp(1,-1,tsz[1],-2);
		update(1);
	}
};

CentroidD cd;

int main(){

	fastio;
	int n,m,a,b;
	cin >> n >> m;
	for(int i = 1; i < n; ++i){
		cin >> a >> b;
		cd.addEdge(a,b);
	}

	cd.init(n);

	int t,u;
	while(m--){
		cin >> t >> u;
		if(t == 1) cd.update(u);
		else cd.query(u);
	}

	return 0;
}
