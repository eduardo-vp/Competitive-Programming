#include <bits/stdc++.h>

#define INF 1e9
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); i++)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 250
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef long double ld;
typedef pair<ld,ii> iii;

int n;
int x[N],y[N];
ld ans;
ii fred,fiona;
vector<iii> edges;
vector< pair<ld,int> > adj[N];

int p[N],rk[N];
void init(int n){ FOR(i,0,n) p[i] = i, rk[i] = 0; }
int findSet(int i){ return (p[i] == i) ? (i) : (p[i] = findSet(p[i])); }
bool isSameSet(int i, int j){ return findSet(i) == findSet(j); }
void unionSet(int i, int j){
	int x = findSet(i), y = findSet(j);
	if(rk[x] > rk[y]) p[y] = x;
	else{
		p[x] = y;
		if(rk[x] == rk[y]) rk[y]++;
	}
}


void kruskal(){
	sort(edges.begin(),edges.end());
	init(n);
	FOR(i,0,edges.size()){
		iii tri = edges[i];
		ld w = tri.fst;
		int x = tri.snd.fst, y = tri.snd.snd;
		if(!isSameSet(x,y)){
			unionSet(x,y);
			adj[x].pb(mp(w,y));
			adj[y].pb(mp(w,x));
		}
	}
}

void dfs(int u){
	FOR(i,0,adj[u].size()){
		int v = adj[u][i].snd;
		if(p[v] == -1){
			p[v] = u;
			dfs(v);
		}
	}
}

void augment(int x, ld maxEdge ){
	if(x == 0) ans = maxEdge;
	else{
		int u = p[x];
		ld cur = 0;
		FOR(i,0,adj[u].size()){
			int v = adj[u][i].snd;
			if(v == x){ cur = adj[u][i].fst; break; }
		}
		augment(p[x],max(maxEdge,cur));
	} 
}

int main(){

	int tc = 1;
	while(cin >> n and n){
		FOR(i,0,n)
			cin >> x[i] >> y[i];
		fred = ii(x[0],y[0]);
		fiona = ii(x[1],y[1]);
		FOR(i,0,n)
			FOR(j,i+1,n){
				ld dist = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j]) * (y[i]-y[j]);
				dist = sqrt(dist);
				edges.pb(mp(dist,ii(i,j)));
			}
		
		kruskal();
		FOR(i,0,n) p[i] = -1;
		p[0] = 0;
		dfs(0);
		augment(1,0);

		printf("Scenario #%d\n",tc++);
		cout << "Frog Distance = " << setprecision(3) << fixed << ans << endl << endl;

		FOR(i,0,n)
			adj[i].clear();
		edges.clear();
	}

    return 0;
}