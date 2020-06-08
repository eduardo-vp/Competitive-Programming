#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define trace(x) cout << #x << " = " << x << endl

using namespace std;

typedef pair<int,int> ii;
typedef pair<double,ii> dii;

int s,out,x,y,p[550],rk[550];
vector<dii> edges;

int find(int x){ return (p[x] == x) ? x : (find(p[x])); }
bool isSameSet(int x, int y){ return find(x) == find(y); }
void unionSet(int i, int j){
	int x = find(i), y = find(j);
	if(rk[x] > rk[y]) p[y] = x;
	else{
		p[x] = y;
		if(rk[x] == rk[y]) rk[y]++;
	}
}

double kruskal(){
	int aris = 0;
	sort(edges.begin(),edges.end());
	double ans = 0;
	for(int i = 0; i < int(edges.size()) and (aris < out-s); i++){
		int x = edges[i].second.first, y = edges[i].second.second;
		if(!isSameSet(x,y)){
			unionSet(x,y);
			ans = max(ans,edges[i].first);
			aris++;
		}
	}
	return ans;
}

int main(){

	int tc;
	int point[550][2];
	cin >> tc;
	while(tc--){
		cin >> s >> out;
		for(int i = 0; i < out; i++)
			cin >> point[i][0] >> point[i][1];
		for(int i = 0; i < out; i++)
			for(int j = i+1; j < out; j++){
				double dist = sqrt( pow(point[i][0]-point[j][0],2) + pow(point[i][1]-point[j][1],2) );
				edges.pb(mp(dist,ii(i,j)));
			}
		for(int i = 0; i < out; i++) p[i] = i;
		fill(rk,0);
		printf("%.2lf\n",kruskal());
		edges.clear();
	}

	return 0;
}