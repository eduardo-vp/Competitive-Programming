#include <bits/stdc++.h>

#define INF 1000000000
#define mp make_pair
#define sqr(x) x*x
#define pb push_back
#define fst first
#define snd second
#define FOR(i,a,b) for(int i = int(a); i < int(b); i++)
#define trace(x) cout << #x << " = " << x << endl
#define trace2(x,y) cout << #x << " = " << x << " " << #y << " = " << y << endl  
#define N 150

using namespace std;

typedef long double ld;
typedef pair<int,int> ii;
typedef pair<ld,ii> iii;

int n;
int p[N],rk[N];
ld x[N],y[N];
vector<iii> edges;

void init(){ FOR(i,0,n) p[i] = i, rk[i] = 0; }
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

ld kruskal(){
	ld ans = 0;
	init();
	sort(edges.begin(),edges.end());
	FOR(i,0,edges.size()){
		iii tri = edges[i];
		ld cost = tri.fst;
		int x = tri.snd.fst, y = tri.snd.snd;
		if(!isSameSet(x,y)){
			unionSet(x,y);
			ans += cost;
		}
	}
	return ans;
}

int main(){

	int tc;
	cin >> tc;
	FOR(TC,0,tc){
		if(TC) cout << endl;
		cin >> n;
		FOR(i,0,n) cin >> x[i] >> y[i];
		FOR(i,0,n){
			FOR(j,i+1,n){
				//trace2(x[i],y[i]);
				//trace2(x[j],y[j]);
				ld dist = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
				dist = sqrt(dist);
				//trace(dist);
				edges.pb(mp(dist,ii(i,j)));
			}
		}
		cout << setprecision(2) << fixed << kruskal() << endl;
		edges.clear();
	}

	return 0;
}