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
#define N 3100
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef long double ld;

ll n,a,b,x;
// dp[i][j] prob de ganar habiendo restado i icpcs y j normales
ld dp[N][N];

ld getProb(ll icpc, ll nrm){
    if( dp[icpc][nrm] >= (-0.1) ) return dp[icpc][nrm];
    ll used = icpc + nrm;
    if(used >= n) return 0.0;
    dp[icpc][nrm] = 0.000000000;
    ll curicpc = a - icpc;
    ll curnrm = b - nrm;
    ll total = 2*curicpc + curnrm + x;
    // gana el sujeto
    dp[icpc][nrm] += ld(x)/ld(total);
    // gana un icpc
    if(curicpc > 0)
        dp[icpc][nrm] += ld(2*curicpc)/ld(total) * getProb(icpc+1,nrm);
    // gana un nrm
    if(curnrm > 0)
        dp[icpc][nrm] += ld(curnrm)/ld(total) * getProb(icpc,nrm+1);
    return dp[icpc][nrm];
}

int main(){

    fastio;
    while(cin >> n >> a >> b){
        for(x = 2LL; x >= 1LL; x--){
            FOR(i,0,N) FOR(j,0,N) dp[i][j] = -1.0000;
            getProb(0,0);
            cout << setprecision(10) << fixed << dp[0LL][0LL] << endl;
        }
    }

    return 0;
}