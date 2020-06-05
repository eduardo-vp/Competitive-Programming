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

#define N 100005
#define mod 998244353
#define N1 1010
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
struct T{
  ll fmx, smx, cmx;
  T(){}
  T(ll fmx, ll smx, ll cmx): fmx(fmx), smx(smx), cmx(cmx) {}
};

struct ST{
  ll n; 
  T lazy[4*N];
  ll tree[4*N], ar[N];
  set<ll> s;
  inline ll OpT(ll &val1, ll &val2){
    return val1+val2;
  }
  inline T OpL(T &val1, T &val2){
    T ty;
    s.clear();
    s.insert(val1.fmx), s.insert(val1.smx);
    s.insert(val2.fmx), s.insert(val2.smx);
    auto it=s.end(); it--;
    ty.fmx=*it; it--; ty.cmx=0;
    ty.smx=*it; s.clear();
    if(ty.fmx==val1.fmx) ty.cmx+=val1.cmx;
    if(ty.fmx==val2.fmx) ty.cmx+=val2.cmx;
    return ty;
  }
  inline void updatepro(T laz, ll id, ll l, ll r){
    ll t1=laz.fmx, t2=laz.smx;
    ll c1=laz.cmx;
    if(lazy[id].fmx>t1){
      tree[id]-=lazy[id].cmx*(lazy[id].fmx-t1);
      lazy[id].fmx=t1;
    }
  }
  inline void proh(ll id, ll l, ll r){
    if(l+1==r) return;
    ll mid=(l+r)>>1;
    updatepro(lazy[id], id<<1, l, mid);
    updatepro(lazy[id], id<<1|1, mid, r);
    //lazy[id]=neutro
  }
  inline void updateRange(ll x, ll y, T val, ll id, ll l, ll r){
    proh(id, l, r);
    if(x>=r || y<=l || lazy[id].fmx<=val.fmx) return;
    if(x<=l && r<=y && lazy[id].fmx>val.fmx && lazy[id].smx<val.fmx){
      updatepro(val, id , l, r);
      return;
    }
    ll mid=(l+r)>>1;
    updateRange(x, y, val, id<<1, l, mid);
    updateRange(x, y, val, id<<1|1, mid, r);
    tree[id]=OpT(tree[id<<1], tree[id<<1|1]);
    lazy[id]=OpL(lazy[id<<1], lazy[id<<1|1]);
  }
  inline ll getSum(ll x, ll y, ll id, ll l, ll r){
    proh(id, l, r);
    if(x>=r || y<=l) return 0;
    if(x<=l && r<=y) return tree[id];
    ll mid=(l+r)>>1;
    ll left, right;
    left=getSum(x, y, id<<1, l , mid);
    right=getSum(x, y, id<<1|1, mid, r);
    return OpT(left, right);
  }
  inline void build1(ll id, ll l, ll r){
    if(l+1==r){
      tree[id]=ar[l], lazy[id].fmx=ar[l];
      lazy[id].smx=-INF, lazy[id].cmx=1;
      return;
    }
    ll mid=(l+r)>>1;
    build1(id<<1, l, mid);
    build1(id<<1|1, mid, r);
    tree[id]=OpT(tree[id<<1], tree[id<<1|1]);
    lazy[id]=OpL(lazy[id<<1], lazy[id<<1|1]);
  }
  inline void upd(ll x, ll y, T val){
    updateRange(x, y, val, 1, 0, n);
  }
  inline ll que(ll x, ll y){
    return getSum(x, y, 1, 0, n);
  }
  inline void build(){
    build1(1, 0, n);
  }
}st;
int main(){
  fastio;
  ll n, m; cin>>n>>m;
  st.n=n;
  FER(i,0,n) cin>>st.ar[i];
  st.build();
  ll type, l, r, x;
  FER(i,0,m){
    cin>>type>>l>>r; l--;
    if(type==1){
      ll froz=st.que(l, r);
      trace(froz);
    }
    else{
      cin>>x;
      T val;
      val.cmx=1, val.fmx=x, val.smx=-INF;
      st.upd(l, r, val);
    }
  }
  /*
i.e.
8 6
8  4 1 8 3 8  4 1
2 1 4 3 
2 1 8 5
2 2 3 2
1 2 6
2 1 6 1
1 1 8
Answer:
1:14
2:11
*/
  return 0;
}