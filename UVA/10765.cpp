#include <bits/stdc++.h>
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1000000000
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 10100
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int n,m;
int cont,num[N],low[N];
stack<ii> st;
vector<ii> ans;
vector< vector<ii> > biconn;
vector< vector<int> > adj;

void getBiconn(int u, int v){
	if(st.empty()) return;
	ii top;
	vector<ii> vec;
	set<int> s;
	do{
		top = st.top();
		st.pop();
		vec.pb(top);
		s.insert(top.fst); s.insert(top.snd);
	}while(!st.empty() and top != ii(u,v));
	biconn.pb(vec);
	for(set<int>::iterator it = s.begin(); it != s.end(); ++it)
		ans[*it].snd++;
}

void dfs(int u, int p = -1){
	num[u] = low[u] = ++cont;
	int child = 0;
	FOR(i,0,adj[u].size()){
		int v = adj[u][i];
		if(!num[v]){
			st.push(ii(u,v));
			dfs(v,u);
			low[u] = min(low[u],low[v]);
			child++;
			if(p != -1 and low[v] >= num[u]) getBiconn(u,v);
		}else if(p != v and num[v] < low[u]){ // no estoy seguro si es necesario revisar si es menor
			//  and num[v] < low[u]
			low[u] = min(low[u],num[v]);
			st.push(ii(u,v));
		}
		if(p == -1) getBiconn(0,0);
	}
	
}

bool cmp(ii a, ii b){
	if(a.snd > b.snd) return true;
	else if(a.snd < b.snd) return false;
	if(a.fst < b.fst) return true;
	return false;
}

int main(){

	while(cin >> n >> m and n and m){
		ans.clear();
		biconn.clear();
		FOR(i,0,n) ans.pb(ii(i,0));
		adj.assign(n,vector<int>());
		int a,b;
		while(cin >> a >> b){
			if(a == -1 and b == -1) break;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		cont = 0;
		FOR(i,0,n) num[i] = 0;
		FOR(i,0,n){
			if(!num[i]) dfs(i);
			set<int> s;
			vector<ii> v;
			while(!st.empty()){
				ii top = st.top();
				st.pop();
				s.insert(top.fst); s.insert(top.snd);
				v.pb(top);
			}
			biconn.pb(v);
		}
		sort(ans.begin(),ans.end(),cmp);
		//cout << "ANS:" << endl;
		FOR(i,0,m)
			cout << ans[i].fst << " " << ans[i].snd << endl;
		cout << endl;
	}

    return 0;
}
