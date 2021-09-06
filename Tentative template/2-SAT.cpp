// dile a la jardinera que traigo flores
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

#define N 200005
#define mod 998244353
#define N1 1005
#define sqr(x) (x)*(x)
#define INF 10000000000000

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

struct TWOSAT{
  // assig[i]: 0 pushear, 1: no pushear
  // nodes para el nodo n >> true: 2*n, false:2*n+1 
  vi adj[N], adjt[N];
  ll n;
  ll comp[N], vis[N], assig[N];
  vi eulerian;
  inline void dfs1(ll u){
    vis[u]=1;
    for(auto xd: adj[u]) if(vis[xd]==0) dfs1(xd);
    eulerian.pb(u);
  }
  inline void dfs2(ll u, ll rt){
    comp[u]=rt;
    for(auto xd: adjt[u]) if(comp[xd]==-1) dfs2(xd, rt);
  }
  inline ll solve(){
    fill(vis, 0), fill(comp, -1), fill(assig, 0);
    ll pos=0;
    FER(i,0,n) for(auto xd: adj[i]) adjt[xd].pb(i);
    FER(i,0,n) if(vis[i]==0) dfs1(i);
    reverse(all(eulerian));
    for(auto xd: eulerian) if(comp[xd]==-1) dfs2(xd, pos++);
    FER(i,0,n/2) assig[i]=1;
    for(ll i=0; i<n; i+=2){
      if(comp[i]==comp[i+1]) return 0;
      assig[i/2]=(comp[i]>comp[i+1]);
    }
    return 1;
  }
}sat;
ll val[N];
vi g[N];
int main(){
  fastio;
  ll n, m; cin>>n>>m;
  FER(i,0,n) cin>>val[i];
  ll ta=2*m;
  sat.n=ta;
  FER(i,0,m){
    ll t; cin>>t;
    FER(k, 0, t){
      ll x; cin>>x; x--;
      g[x].pb(i);
    }
  }
  FER(i,0,n){
    ll a=g[i][0], b=g[i][1];
    if(val[i]){
      sat.adj[2*a].pb(2*b);
      sat.adj[2*b].pb(2*a);
      sat.adj[2*a+1].pb(2*b+1);
      sat.adj[2*b+1].pb(2*a+1);
    }
    else{
      sat.adj[2*a].pb(2*b+1);
      sat.adj[2*b+1].pb(2*a);
      sat.adj[2*a+1].pb(2*b);
      sat.adj[2*b].pb(2*a+1);
    }
  }
  ll froz=sat.solve();
  froz? cout<<"YES"<<"\n": cout<<"NO"<<"\n";
  return 0;
}