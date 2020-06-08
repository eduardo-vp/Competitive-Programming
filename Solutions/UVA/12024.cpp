#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1000000000
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); i++)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int dp[15];
int fact[15];

void derangement(){
	dp[0] = 1;
	dp[1] = 0;
	for(int i = 2; i <= 12; i++)
		dp[i] = (i-1)*(dp[i-1]+dp[i-2]);
}

void factorial(){
	fact[0] = 1;
	for(int i = 1; i <= 12; i++)
		fact[i] = i*fact[i-1];
}

int main(){

	derangement();
	factorial();

	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		cout << dp[n] << "/" << fact[n] << endl;
	}

	return 0;
}