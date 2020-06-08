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
#define N 300
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int n,l;
int color[N];
vector<int> adj[N];

bool dfs(int x){
	bool ans = true;
	//trace(x);
	FOR(i,0,adj[x].size()){
		int v = adj[x][i];
		//trace(v);
		if(color[v] == color[x]) return false;
		if(color[v] == -1){
			color[v] = 1-color[x];
			ans = ans and dfs(v);
		}
	}
	return ans;
}

bool check(){
	fill(color,-1);
	color[0] = 0;
	return dfs(0);
}

int main(){

	while(cin >> n and n){
		cin >> l;
		int x,y;
		FOR(i,0,l){
			cin >> x >> y;
			adj[x].pb(y);
			adj[y].pb(x);
		}

		if(!check()) cout << "NOT "; 
		cout << "BICOLORABLE." << endl;

		FOR(i,0,n) adj[i].clear();
	}

	return 0;
}