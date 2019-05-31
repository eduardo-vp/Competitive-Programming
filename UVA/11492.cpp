#include <bits/stdc++.h>
#define INF INT_MAX
#define fst first
#define snd second
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define trace(x) cout << #x << " = " << x << endl
using namespace std;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

/*DIJKSTRA*/

int adj[2500][2];
int dist[2500];
vector<vii> g;
vector<string> words;
map<string,int> lang;
priority_queue<ii,vector<ii>,greater<ii> > pq;

bool valid(int x, int y){
	if(words[x][0] == words[y][0]) return false;
	if( (adj[x][0] == adj[y][0]) or (adj[x][0] == adj[y][1]) ) return true;
	if( (adj[x][1] == adj[y][0]) or (adj[x][1] == adj[y][1]) ) return true;
	return false;
}

void solve(){
	while(!pq.empty()){
		ii t = pq.top(); pq.pop();
		int d = t.fst, u = t.snd;
		if(d > dist[u]) continue;
		for(int i = 0; i < (int)g[u].size(); i++){
			int v = g[u][i].fst, c = g[u][i].snd;
			if(d + c < dist[v]){
				dist[v] = d+c;
				pq.push(ii(dist[v],v));
			}
		}
	}
}

int main(){

	int n;
	string a,b,c;
	string l1,l2;
	fastio;
	while(cin >> n){
		if(n == 0) break;
		int lgCont = 0;
		cin >> l1 >> l2;
		fill(adj,-1);
		vi inicio,obj;
		if(lang.count(a) == 0) lang[a] = lgCont++;
		if(lang.count(b) == 0) lang[b] = lgCont++;
		for(int i = 0; i < n; i++){
			cin >> a >> b >> c;
			if(lang.count(a) == 0) lang[a] = lgCont++;
			if(lang.count(b) == 0) lang[b] = lgCont++;
			adj[i][0] = lang[a];
			adj[i][1] = lang[b];
			words.pb(c);
			if(l1.compare(a) == 0) inicio.pb(i);
			else if(l1.compare(b) == 0) inicio.pb(i);
			if(l2.compare(a) == 0) obj.pb(i);
			else if(l2.compare(b) == 0) obj.pb(i);
		}
		g.assign(n,vii());
		for(int i = 0; i < n-1; i++)
			for(int j = i+1; j < n; j++)
				if( valid(i,j) ){
					//trace(i); trace(j);
					g[i].pb(ii(j,(int)words[j].size()));
					g[j].pb(ii(i,(int)words[i].size()));
				}
		int ans = INF;
		for(int i = 0; i < (int)inicio.size(); i++){
			int u = inicio[i];
			for(int i = 0; i < n; i++) dist[i] = INF;
			dist[u] = (int)words[u].size();
			pq.push(ii(dist[u],u));
			solve();
			for(int i = 0; i < (int)obj.size(); i++)
				ans = min(ans,dist[obj[i]]);
		}
		if(ans == INF) cout << "impossivel" << endl;
		else cout << ans << endl;
		lang.clear();
		words.clear();
		g.clear();
	}

	return 0;
}