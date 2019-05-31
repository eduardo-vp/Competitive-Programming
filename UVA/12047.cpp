#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
#define INF 1e9
#define trace(x) cout << #x << " = " << x << endl
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;

int n,m,s,t,p;
int distS[10500];
int distT[10500];
vector<vii> g, g2;
priority_queue< ii,vector<ii>,greater<ii> > pq;

void solve(){
	while(!pq.empty()){
		ii tp = pq.top(); pq.pop();	
		int d = tp.fst, u = tp.snd;
		if(d > distS[u]) continue;
		for(int i = 0; i < (int)g[u].size(); i++){
			int v = g[u][i].fst, w = g[u][i].snd;
			if(d + w < distS[v]){
				distS[v] = d+w;
				pq.push(ii(distS[v],v));
			}
		}
	}
}

void solve2(){
	while(!pq.empty()){
		ii tp = pq.top(); pq.pop();	
		int d = tp.fst, u = tp.snd;
		if(d > distT[u]) continue;
		for(int i = 0; i < (int)g2[u].size(); i++){
			int v = g2[u][i].fst, w = g2[u][i].snd;
			if(d + w < distT[v]){
				distT[v] = d+w;
				pq.push(ii(distT[v],v));
			}
		}
	}
}

int main(){

	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d%d%d%d%d",&n,&m,&s,&t,&p);
		int u,v,c;
		g.assign(n+5,vii());
		g2.assign(n+5,vii());
		for(int i = 0; i < m; i++){
			scanf("%d%d%d",&u,&v,&c);
			g[u].pb(ii(v,c));
			g2[v].pb(ii(u,c));
		}
		for(int i = 0; i <= n; i++)
			distS[i] = distT[i] = INF;
		distS[s] = distT[t] = 0;
		// first
		pq.push(ii(0,s));
		solve();
		//second
		pq.push(ii(0,t));
		solve2();
		//
		int ans = -1;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < (int)g[i].size(); j++){
				int v = g[i][j].fst, w = g[i][j].snd;
				if( (distS[i] + w + distT[v]) <= p)
					ans = max(ans,w);
			}
		cout << ans << endl;
		g.clear();
		g2.clear();
	}

	return 0;
}