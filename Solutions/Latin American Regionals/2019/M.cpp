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
#define N 1024
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int a[N];

int main(){

  int n,x;
  cin >> n >> x;
  for(int i = 0; i < n; ++i)
    cin >> a[i];
  
  int ans = 0;
  for(int i = 0; i < n; ++i){
    int cur = 1;
    for(int j = i+1; j < n; ++j){
      if(abs(a[j-1]-a[j]) <= x) cur++;
      else break;
    }
    ans = max(ans,cur);
  }
  cout << ans << endl;
  return 0;
}

