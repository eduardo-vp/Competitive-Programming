// dile a la jardinera que traigo flores
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define tm1 ff
#define tm2 ss.ff
#define tm3 ss.ss
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define all(v) (v).begin(),(v).end()
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define IFR(i,a,b) for(int i = int(a); i >= int(b); i--)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 128
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

ll g,p,cont;
ll dist[N],vist[N],dp[N],reach[N];
ll value[N], cost[N];
vector<ii> adj[N];
map<string,ll> getBenf;
map<ll,string> getCad;

bool dfs(ll u){
	if(u == cont) return dp[u] = true;
	if(dp[u] != -1) return dp[u];
	vist[u] = 1;
	bool ans = false;
	for(ii p : adj[u]){
		ll v = p.second;
		if(!vist[v]) ans = dfs(v) or ans;
	}
	return dp[u] = ans;
}

void dfs2(ll u){
	vist[u] = 1;
	reach[u] = 1;
	for(ii p : adj[u]){
		ll v = p.second;
		if(!vist[v]) dfs2(v);
	}
}

bool check(){
	fill(vist,0); fill(reach,0); dfs2(0); 
	fill(vist,0);
	fill(dp,-1); 

	for(ll u = 0; u <= cont; ++u){
		for(ii p : adj[u]){
			ll d = p.ff, v = p.ss;
			if(v == cont) continue;
			if( (dist[v] > dist[u]+d) and dfs(u) and reach[u]) return true;
		}
	}
	return false;
}

int main(){

	fastio;	
	while(cin >> g >> p){
		if(g == -1 and p == -1) break;
		getBenf.clear(); getCad.clear(); 
		
		string cad; ll x;
		FER(i,0,g){
			cin >> cad >> x;
			getBenf[cad] = x;
		}

		cont = 1;
		FER(i,0,p){
			cin >> cad >> x;
			ll l,r;
			for(l = 0; cad[l] != '-'; ++l);
			for(r = sz(cad)-1; cad[r] != '-'; --r);
			ll sum = 0;
			bool gg = false;
			string s;
			while(l < r){
				s = "";
				l++;
				while(cad[l] != '-'){
					s += string(1,cad[l]);
					++l;
				}
				if(getBenf.count(s)){
					sum += getBenf[s];
				}else gg = true;
			}
			if(gg) continue;
			cost[cont] = x;
			value[cont] = sum;
			getCad[cont] = cad;
			cont++;
		}

		FER(i,0,cont+1) adj[i].clear();
		FER(i,0,cont+1) dist[i] = 1e18;

		// de 0 al resto del grafo
		for(ll i = 1; i < cont; ++i){
			string s = getCad[i];
			string cur = "";
			for(ll l = 0; s[l] != '-'; ++l)
				cur += string(1,s[l]);
			if(getBenf.count(cur))
				adj[0].pb(ii(cost[i]-getBenf[cur]-value[i],i));
		}

		// del i al j
		for(ll i = 1; i < cont; ++i){
			string x = getCad[i];
			string a = "";
			for(ll k = sz(x)-1; x[k] != '-'; --k)
				a += string(1,x[k]);
			reverse(a.begin(),a.end());
			for(ll j = 1; j < cont; ++j){
				string y = getCad[j];
				string b = "";
				for(ll k = 0; y[k] != '-'; ++k)
					b += string(1,y[k]);
				string c = a + b;
				//trace(a,b,c);
				if(getBenf.count(c))
					adj[i].pb({cost[j]-value[j]-getBenf[c],j});
			}
		}
		
		// de nodos al cont
		for(ll i = 1; i < cont; ++i){
			string x = getCad[i];
			string a = "";
			for(ll k = sz(x)-1; x[k] != '-'; --k)
				a += string(1,x[k]);
			reverse(a.begin(),a.end());
			if(getBenf.count(a))
				adj[i].pb({-getBenf[a],cont});
		}

		dist[0] = 0; 
		// Bellman Ford
		for(ll i = 0; i < cont; ++i){
			for(ll u = 0; u <= cont; ++u){
				for(ii p : adj[u]){
					ll d = p.first, v = p.second;
					dist[v] = min(dist[v],dist[u]+d);
				}
			}
		}

		dist[cont] = min(dist[cont],0LL);
		// check for infinity
		if(check()) cout << "*" << endl;
		else cout << -dist[cont] << endl;
	}
	
	return 0;
}