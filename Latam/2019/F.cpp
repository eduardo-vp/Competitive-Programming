// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf // clear structures // statement
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define REP(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 5050
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const int MOD = 1e9+7;

int dp[N][N];

void sum(int &a, const int &b){ if((a += b) >= MOD) a -= MOD; }

void build(){
	REP(i,0,N) dp[0][i] = 1;
	REP(i,0,N) dp[i][1] = 1;
	for(int i = 1; i < N; ++i){
		int diag = dp[i-1][1], acum = dp[i-1][1];
		for(int j = 2; j < N; ++j){
			if(i-j >= 0) sum(diag,dp[i-j][j]);
			sum(acum,diag);
			dp[i][j] = acum;
		}
	}
}

int main(){

	fastio;
	build();
	int b,s;
	cin >> s >> b;
	cout << dp[b-s][s] << endl;

	return 0;
}

