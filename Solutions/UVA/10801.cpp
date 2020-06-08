#include <bits/stdc++.h>
#define INF INT_MAX
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define mp make_pair
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int n,k;
int tiempo[7],dist[100][7];

vector< set<int> > floors;
priority_queue<iii,vector<iii>,greater<iii> > pq;

void solve(){
	while(!pq.empty()){
		iii t = pq.top(); pq.pop();
		int d = t.first, f = t.second.first, e = t.second.second;
		if(d > dist[f][e]) continue;
		set<int> s = floors[e];
		for(set<int>::iterator it = s.begin(); it != s.end(); it++){
			int v = *it;
			if( (abs(v-f)*tiempo[e] + d) < dist[v][e]){
				dist[v][e] = abs(v-f)*tiempo[e] + d;
				pq.push(mp( abs(v-f)*tiempo[e] + d,ii(v,e) ));
			}
		}
		for(int i = 0; i < n; i++){
			if(floors[i].count(f) and (d + 60) < dist[f][i] ){
				pq.push(mp( d+60,ii(f,i) ));
			}
		}
	}
}

int main(){

	string cad;
	int tc = 1;
	while(cin >> n >> k){
		for(int i = 0; i < n; i++)
			scanf("%d",tiempo+i);
		cin.ignore();
		for(int i = 0; i < n; i++){
			getline(cin,cad);
			set<int> s;
			int x;
			istringstream iss(cad);
			while(iss >> x) s.insert(x);
			floors.pb(s);
		}
		
		for(int i = 0; i < 100; i++)
			for(int j = 0; j < n; j++) dist[i][j] = INF;
		for(int i = 0; i < n; i++)
			if(floors[i].count(0)){
				pq.push(mp(0,ii(0,i))); dist[0][i] = 0;
			}
		
		solve();
		int ans = INF;
		for(int i = 0; i < n; i++)
			ans = min(ans,dist[k][i]);
		//cout << "TC " << tc++ << " ";
		if(ans != INF) cout << ans << endl;
		else cout << "IMPOSSIBLE" << endl;
		floors.clear();
	}

	return 0;
}