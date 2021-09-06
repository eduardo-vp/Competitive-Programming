// dile a la jardinera que traigo flores
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define tm1 ff
#define tm2 ss.ff
#define tm3 ss.ss
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define all(v) (v).begin(),(v).end()
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define IFR(i,a,b) for(int i = int(a); i >= int(b); i--)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 100020
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 1e9;
int n,h;
int pos[1024],dp[50010][1010];

int solve(int p, int n){
  if(p < 0) return -INF;
  if(dp[p][n] != -1) return dp[p][n];
  if(p == 0 or n == 0) return -INF;
  int prev = pos[n-1];
  int dif = p - prev;
  int ans = -INF;
  if(dif <= h) ans = max(ans,solve(prev,n-1)+(pos[n] == p));
  ans = max(ans,solve(p-h,n-1) + (pos[n] == p));
  return dp[p][n] = ans;
}

int main(){

  fastio; 
  int x;
  while(cin >> n >> h){
    if(n == -1 and h == -1) break;
    fill(pos,-1);
    pos[0] = 0;
    int sum = 0;
    FER(i,0,n-1){
      cin >> x;
      sum += x;
      pos[i+1] = sum;
    }
    if(sum > h*(n-1)){ cout << -1 << endl; continue; }
    FER(i,0,sum+1) FER(j,0,n) dp[i][j] = -1;
    dp[0][0] = 1;
    int ans = solve(sum,n-1);
    cout << (n-ans) << endl;
  }
  
  return 0;
}