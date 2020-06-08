// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 1050
#define LGMAX 10
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int dp[N][N],flog[N];
char tab[N][N];

void build(int n){
	for(int lg = 0, pw = 1; pw < n;){
		FER(i,pw,min(2*pw,n)) flog[i] = lg;
		lg++; pw *= 2;
	}
}

struct ST{
	int n;
	int rmq[N][LGMAX];
	ST(){}
	void build(vector<int> &vec){
		n = sz(vec);
		for(int i = 0; i < n; ++i)
			rmq[i][0] = vec[i];
		for(int lg = 1, pw = 2; lg < LGMAX; ++lg, pw *= 2){
			for(int i = 0; i < n; ++i){
				if(i+pw/2 < n) rmq[i][lg] = min(rmq[i][lg-1],rmq[i+pw/2][lg-1]);
				else rmq[i][lg] = rmq[i][lg-1];
			}
		}
	}

	int query(int i, int j){
		if(i == j) return rmq[i][0];
		int lg = flog[j-i];
		int pw = (1 << lg);
		return min(rmq[i][lg],rmq[j-pw+1][lg]);
	}
};

ST st[N];

int main(){

	int n,m;
	scanf("%d %d",&n,&m);
	build(N);
	FER(i,0,n) FER(j,0,m) scanf(" %c",&tab[i][j]);

	fill(dp,0);
	for(int i = 0; i < n; ++i){
		dp[i][m-1] = 1;
		for(int j = m-2; j >= 0; --j){
			if(tab[i][j] == tab[i][j+1]) dp[i][j] = dp[i][j+1]+1;
			else dp[i][j] = 1;
		}
	}

	vector<int> vec(n);
	for(int j = 0; j < m; ++j){
		for(int i = 0; i < n; ++i){
			vec[i] = dp[i][j];
		}
		st[j].build(vec);
	}

	int ans = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			int lo = i, hi = n;
			while(hi - lo > 1){
				int mid = (lo+hi) >> 1;
				if(st[j].query(i,mid) >= (mid-i+1)) lo = mid;
				else hi = mid;
			}
			ans = max(ans,lo-i+1);
		}
	}
	cout << ans*ans << endl;
	return 0;
}

