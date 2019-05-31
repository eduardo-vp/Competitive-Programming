#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1e9
#define fill(x,v) memset(x,v,sizeof(x))
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int dist[150], floyd[150][150];
int ans,s,d;
vector<vi> g;
queue<int> cola;

void bfs(){
	ans = floyd[s][d];
	while(!cola.empty()){
		int u = cola.front(); cola.pop();
		for(int i = 0; i < int(g[u].size()); i++){
			int v = g[u][i];
			if(dist[v] == INF){
				dist[v] = dist[u]+1;
				cola.push(v);
				ans = max(ans,dist[v]+floyd[v][d]);
				//trace(v); trace(d); trace(floyd[v][d]);
			}
		}
	}
}

int main(){

	int tc,cont = 1;
	cin >> tc;
	while(tc--){
		int n,r,x,y;
		cin >> n >> r;
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++)
				floyd[i][j] = INF;
			floyd[i][i] = 0;
		}

		g.assign(n,vi());
		for(int i = 0; i < r; i++){
			cin >> x >> y;
			g[x].pb(y); g[y].pb(x);
			floyd[x][y] = floyd[y][x] = 1;
		}

		//floyd
		for(int k = 0; k < n; k++)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					floyd[i][j] = min(floyd[i][j],floyd[i][k]+floyd[k][j]);

		cin >> s >> d;
		//trace(s);trace(d);
		FOR(i,0,n) dist[i] = INF;
		dist[s] = ans = 0;
		cola.push(s);
		bfs();
		cout << "Case " << cont++ << ": " << ans << endl;
	}	

	return 0;
}