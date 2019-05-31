#include <bits/stdc++.h>
#define INF INT_MAX
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef pair<int,int> ii;

int x,y,r,c;
queue<ii> cola;
int tab[1050][1050];
int dist[1050][1050];

int dr[] = {0,1,0,-1};
int dc[] = {1,0,-1,0};

void bfs(){
	while(!cola.empty()){
		ii t = cola.front(); cola.pop();
		int a = t.first, b = t.second;
		for(int i = 0; i < 4; i++){
			int aa = a+dr[i], bb = b+dc[i];
			if( (aa >= 0) and (aa < r) and (bb >= 0) and (bb < c) and (dist[aa][bb] == INF) and (tab[aa][bb] == 0) ){
				dist[aa][bb] = dist[a][b] + 1;
				cola.push(ii(aa,bb));
			}
		}
	}
}

int main(){

	int n,m,z,ind,a,b;
	fastio;
	while(cin >> r >> c){
		if(r == 0 and c == 0) break;
		cin >> n;
		fill(tab,0);
		for(int i = 0; i < n; i++){
			cin >> ind >> m;
			for(int j = 0; j < m; j++){
				cin >> z;
				tab[ind][z] = 1;
			}
		}
		cin >> a >> b >> x >> y;
		cola.push(ii(a,b));
		for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) dist[i][j] = INF;
		dist[a][b] = 0;
		bfs();
		cout << dist[x][y] << endl;
	}

	return 0;
}