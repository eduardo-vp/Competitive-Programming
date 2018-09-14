// REVENGE, HONOR AND PRIDE
#include <bits/stdc++.h>
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1000000000
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define MOD 1000000007
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

void Mul(ll a[2][2], ll b[2][2], ll c[2][2]){
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 2; ++j){
            c[i][j] = 0;
            for(int k = 0; k < 2; ++k)
                c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % MOD;
        }
    }
}

void binPow(ll x[2][2], ll p, ll ans[2][2]){
    ll temp[2][2];
    ans[0][0] = ans[1][1] = 1;
    ans[0][1] = ans[1][0] = 0;
    while(p){
        if(p & 1){
            Mul(ans,x,temp);
            FOR(i,0,2) FOR(j,0,2) ans[i][j] = temp[i][j];
        }
        p >>= 1;
        Mul(x,x,temp);
        FOR(i,0,2) FOR(j,0,2) x[i][j] = temp[i][j];
    }
}

int fib(int x){
    if(x <= 2) return 1;
    ll z[2][2], ans[2][2];
    z[0][0] = z[0][1] = z[1][0] = 1;
    z[1][1] = 0;
    binPow(z,x-2,ans);
    return (ans[0][0] + ans[0][1] ) % MOD;
}

int main(){

    int tc,x;
    cin >> tc;
    FOR(i,0,tc){
        cin >> x;
        cout << fib(x) << endl;
    }

    return 0;
}
