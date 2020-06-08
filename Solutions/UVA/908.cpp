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
#define N 1000000
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int n,second;
int p[N],rk[N];
vector<iii> edges;

void init(){ for(int i = 1; i <= n; i++) p[i] = i, rk[i] = 0; }
int findSet(int i){ return (p[i] == i) ? (i) : (p[i] = findSet(p[i]));  }
bool isSameSet(int x, int y){ return findSet(x) == findSet(y); }
void unionSet(int i, int j){
	int x = findSet(i), y = findSet(j);
	if(rk[x] > rk[y]) p[y] = x;
	else{
		p[x] = y;
		if(rk[x] == rk[y]) rk[y]++;
	}
}

void kruskal(){
	second = 0;
	init();
	sort(edges.begin(),edges.end());
	FOR(i,0,edges.size()){
		iii tri = edges[i];
		ii p = tri.snd;
		if(!isSameSet(p.fst,p.snd)){
			unionSet(p.fst,p.snd);
			second += tri.fst;
		}
	}
}

int main(){

    bool line = false;
    while(cin >> n){
    	if(!line) line = true; else cout << endl;
    	int a,b,c;
    	int first = 0;
    	FOR(i,0,n-1){
    		cin >> a >> b >> c;
    		first += c;
    	}
    	int k; cin >> k;
    	FOR(i,0,k){
    		cin >> a >> b >> c;
    		edges.pb(mp(c,ii(a,b)));
    	}
    	int m; cin >> m;
    	FOR(i,0,m){
    		cin >> a >> b >> c;
    		edges.pb(mp(c,ii(a,b)));
    	}
    	kruskal();
    	cout << first << endl;
    	cout << second << endl;
    	edges.clear();
    }

    return 0;
}