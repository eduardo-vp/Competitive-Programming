// dile a la jardinera que traigo flores
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 128
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int n,m,ans;
int tab[N][N], vist[N][N];

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

bool validx(int x){ return x > 0 and x < n-1; }
bool validy(int y){ return y > 0 and y < m-1; }

int bfs(int x, int y, vector<ii> &vec){
	int lo = INT_MAX;
	queue<ii> q;
	for(ii p : vec) q.push(p);
	while(!q.empty()){
		ii t = q.front(); q.pop();
		int i = t.ff, j = t.ss;
		FER(k,0,4){
			int ni = i + dx[k], nj = j + dy[k];
			if(validx(ni) and validy(nj) and !vist[ni][nj] and tab[ni][nj] == tab[x][y]){
				vist[ni][nj] = 1;
				q.push(ii(ni,nj));
				vec.pb(ii(ni,nj));
			}
		}
	}
	for(ii p : vec){
		int x = p.ff, y = p.ss;
		FER(k,0,4){
			int nx = x + dx[k], ny = y + dy[k];
			if(!vist[nx][ny]) lo = min(lo,tab[nx][ny]);
		}
	}
	if(lo <= tab[x][y] ) return 0;
	int ans = (lo - tab[x][y])*sz(vec);
	for(ii p : vec)
		tab[p.ff][p.ss] = lo;
	return ans;
}

void expand(int x, int y){
	int amt;
	fill(vist,0);
	vist[x][y] = 1;
	vector<ii> vec; vec.pb(ii(x,y)); vist[x][y] = 1;
	while( (amt = bfs(x,y,vec)) )
		ans += amt;
}

int main(){

	fastio;
	int tc;
	cin >> tc;
	while(tc--){
		ans = 0;
		cin >> n >> m;
		vector< pair<int,ii> > vec;
		FER(i,0,n) FER(j,0,m){
			cin >> tab[i][j];
			vec.pb(mp(tab[i][j],ii(i,j)));
		}
		sort(vec.begin(),vec.end());
		fill(vist,0);
		for(pair<int,ii> tri : vec){
			int x = tri.ss.ff, y = tri.ss.ss;
			if(!validx(x) or !validy(y)) continue;
			expand(x,y);
		}
		cout << ans << endl;
	}

	return 0;
}
