#include <bits/stdc++.h>

#define INF 1e9
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define t 1900
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int res[2500][2500];
int visited[2500], p[2500];
char tab[45][45];
int flow,maxflow;

void augment(int x, int minEdge){
	if(x == 0) flow = minEdge;
	else if(p[x] != -1){
		augment(p[x],min(minEdge,res[p[x]][x]));
		res[p[x]][x] -= flow;
		res[x][p[x]] += flow;
	}
}

int main(){

	int r,c,lim;
	char car;
	while(cin >> r >> c >> lim){
		fill(res,0);
		for(int i = 0; i < r; i++)
			for(int j = 0; j < c; j++){
				int x = (i*c+j)*2+1;
				cin >> car;
				tab[i][j] = car;
				int w;
				if(car == '~') w = 0;
				else if(car == '@') w = INF;
				else if(car == '.') w = 1;
				else if(car == '*'){
					w = 1;
					res[0][x] = 1;
				}else if(car == '#'){
					w = INF;
					res[x+1][t] = lim;
				}
				res[x][x+1] = w;
				if(j > 0 and tab[i][j-1] != '~')
					res[x+1][x-2] = res[x-1][x] = INF;
				if(i > 0 and tab[i-1][j] != '~'){
					int newx = ((i-1)*c+j )*2+1;
					res[x+1][newx] = res[newx+1][x] = INF;
				}
			}
		maxflow = 0;
		while(1){
			flow = 0;
			queue<int> q; q.push(0);
			fill(visited,0); 
			memset(p,-1,sizeof(p));
			while(!q.empty()){
				int u = q.front(); q.pop();
				if(u == t) break;
				for(int i = 1; i <= 1900; i++){
					if(!visited[i] and res[u][i] > 0)
						visited[i] = 1, q.push(i), p[i] = u;
				}
			}
			augment(t,INT_MAX);
			if(flow == 0) break;
			maxflow += flow;
		}
		cout << maxflow << endl;
	}

	return 0;
}