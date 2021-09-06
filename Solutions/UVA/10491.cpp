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

int main(){

  long double n,c,m;

  while(cin >> n >> c >> m){
    long double ans = (n)*c + (c-1)*c;
    ans /= (c+n-m-1)*(c+n);
    cout << setprecision(5) << fixed << ans << endl;
  }

  return 0;
}