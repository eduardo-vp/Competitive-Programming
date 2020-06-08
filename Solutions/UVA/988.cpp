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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

vector< vector<int> > g;
ll ways[500];

int getRow(char c){
	if(c >= '0' and c <= '9') return c - '0';
	return c - 'A'+10;
}

inline int getId(int c, int f, int n){
	return (c*n+f);
}

int main(){

	string cad;
	while(cin >> cad){
		int n = (int)cad.size();
		int t = n*n+1;
		g.assign(n*n+5,vector<int>());
		fill(ways,0);
		//primera parte
		if(cad[0] == '?'){
			for(int i = 1; i <= n; i++) g[0].pb(i);
		}else{
			g[0].pb(getRow(cad[0]));
		}
		// los del medio
		for(int c = 0; c < n-1; c++){
			for(int f = 1; f <= n; f++){
				int id = c*n+f;
				if(cad[c+1] != '?'){
					if( abs(getRow(cad[c+1])-f) > 1 )
						g[id].pb(getId(c+1,getRow(cad[c+1]),n));
				}else{
					for(int i = 1; i <= n; i++){
						if(abs(f-i) > 1)
							g[id].pb(getId(c+1,i,n));
					}
				}
			}
		}
		// ultima capa
		if(cad[n-1] == '?'){
			for(int i = 1; i <= n; i++){
				int id = getId(n-1,i,n);
				g[id].pb(t);
			}
		}else{
			int id = getId(n-1,getRow(cad[n-1]),n);
			g[id].pb(t);
		}

		ways[0] = 1;
		for(int i = 0; i <= n*n; i++){
			for(int j = 0; j < int(g[i].size()); j++){
				int v = g[i][j];
				ways[v] += ways[i];
			}
		}
		cout << ways[t] << endl;
	}	

	return 0;
}