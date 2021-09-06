#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
 
#define pb push_back
#define ff  first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) ll(x.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
 
#define N 8800015
#define M 21
#define sqr(x) (x)*(x)
#define INF 20000000000000000
#define mod 1000000007
#define bas 31
#define pi acos(-1) 
 
using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii > tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> set_t;
 
#define trace(...) f(#__VA_ARGS__, __VA_ARGS__)
 
template<typename t> void f(const char* x, t&& val1){
    cout<<x<< " : "<<val1<<endl;
}
template<typename t1, typename... t2> void f(const char* x, t1&& val1, t2&&... val2){
    const char* xd=strchr(x+1, ',');
    cout.write(x, xd-x)<<" : "<<val1<<" | ";
    f(xd+1, val2...);
}


// Function Pi(n), based on Endargorion's aproach
// that uses THE MEISSEL-LEHMER, to find phi function
// Pi[n]=phi(x, a)+a-1-P_{2}(x, a), pow(n, 1/3)<=x<=pow(n, 1/2)
// So we can take a = pow(n, 1/3)
// P_{k}(x, a): Numbers <=x  with exactly k prime factors, all larger than p_{a}
// p_{a}: a-esimo prime number;
// phi(x, a): Numbers<=x with all prime factors greater than p_{a}


ll vis[10000005], cant[10000005], phi[100005][105];
vi primos;

inline ll FindPhi(ll x, ll p){
  if(!p) return x;
  if(primos[p-1]>=x) return 1;
  if(x<=1e5 && p<=1e2) return phi[x][p];
  return FindPhi(x, p-1)-FindPhi(x/primos[p-1], p-1);
}

inline ll PiFuncion(ll n){
  if(n<1e7) return cant[n];
  ll raizC2=sqrt(n), raizC3=pow(n, 1.0/3.0);
  ll m=PiFuncion(raizC3);
  ll ans=FindPhi(n, m)+m-1;
  for(ll i=m; primos[i]<=raizC2; i++){
    ans-=PiFuncion(n/primos[i]);
    ans+=PiFuncion(primos[i]);
    ans--;
  }
  return ans;
}
int main(){
  fastio;
  FER(i,2,1e7){
    cant[i]+=cant[i-1];
    if(vis[i]) continue;
    cant[i]++;
    primos.pb(i);
    for(ll j=i*i; j<1e7; j+=i) vis[j]++;
  }
  FER(i,0,101){
    FER(j,0,1e5+1) phi[j][i]=i? phi[j][i-1]-phi[j/primos[i-1]][i-1]: j;
  }
  ll n, ans=0; cin>>n;
  for(auto xd: primos){
    ll x=xd, y=n/xd;
    if(sqr(x)>n) break;
    ans+=PiFuncion(y)-PiFuncion(x);
  }
  for(auto xd: primos) {
    if(sqr(xd)*xd<=n) ans++;
    else break;
  }
  cout<<ans<<endl;
  return 0;
}
