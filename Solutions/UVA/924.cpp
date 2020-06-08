#include <bits/stdc++.h>
#define INF INT_MAX
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;
typedef vector<int> vi;

int m,d,boom[3000];
vi dist;
vector<vi> g;
queue<int> cola;

void bfs(){
	while(!cola.empty()){
		int u = cola.front(); cola.pop();
		for(int i = 0; i < int(g[u].size()); i++){
			int v = g[u][i];
			if(dist[v] == INF){
				dist[v] = dist[u]+1;
				boom[dist[v]]++;
				if(boom[dist[v]] > m){
					m = boom[dist[v]]; d = dist[v];
				}
				cola.push(v);
			}
		}
	}
}

int main(){

	int e,t,n,x;
	cin >> e;
	g.assign(e,vi());
	
	for(int i = 0; i < e; i++){
		cin >> n;
		for(int j = 0; j < n; j++){
			cin >> x;
			g[i].pb(x);
		}
	}

	cin >> t;
	for(int i = 0; i < t; i++){
		cin >> x;
		dist.assign(e,INF); dist[x] = 0;
		cola.push(x);
		m = d = 0; fill(boom,0);
		bfs();
		if(m != 0) cout << m << " " << d << endl;
		else cout << 0 << endl;
	}

	return 0;
}