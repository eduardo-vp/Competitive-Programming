// i will show you da wae
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 100050
#define INF 1000000000
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int n,cont;
int t[2*N],pai[N],dep[N],sz[N],id[N],head[N],getNode[N];
vector<int> adj[N];

void build(){
	for(int i = n-1; i > 0; --i) t[i] = INF;
}

void modify(int p){
	p += n;
	if(t[p] == INF) t[p] = p-n;
	else t[p] = INF;
	while(p >>= 1)
		t[p] = min(t[p<<1],t[p<<1|1]);
}

int stquery(int l, int r){
	int ans = INF;
	for(l += n, r += n; l < r; l >>= 1, r >>= 1){
		if(l&1) ans = min(ans,t[l++]);
		if(r&1) ans = min(ans,t[--r]);
	}
	return ans;
}

int makesz(int u, int p = -1, int d = 0){
	pai[u] = p;
	dep[u] = d;
	sz[u] = 1;
	for(int v : adj[u]) if(v != p){
		sz[u] += makesz(v,u,d+1);
	}
	return sz[u];
}

void makehld(int u, int root = 1){
	head[u] = root;
	getNode[cont] = u;
	id[u] = cont++;
	t[id[u]+n] = INF;
	int w = 0,best = -1;
	for(int v : adj[u]) if(v != pai[u]){
		if(sz[v] > best) best = sz[v], w = v;
	}
	if(w) makehld(w,root);
	for(int v : adj[u]) if(v != pai[u] and v != w){
		makehld(v,v);
	}
}

void change(int u){
	modify(id[u]);
}

int query(int u){
	int ans = INF;
	while(u != -1){
		if(head[u] == head[1]){
			ans = min(ans,stquery(id[1],id[u]+1));
			u = -1;
		}else{
			ans = min(ans,stquery(id[head[u]],id[u]+1));
			u = pai[head[u]];
		}
	}
	if(ans == INF) return -1;
	return getNode[ans];
}

int main(){
    
	fastio;
	int q,a,b;
	cin >> n >> q;
	FOR(i,0,n-1){
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	cont = 0;
	makesz(1);
	makehld(1);
	build();
	while(q--){
		cin >> a >> b;
		if(a == 0) change(b);
		else cout << query(b) << endl;
	}

    return 0;
}
