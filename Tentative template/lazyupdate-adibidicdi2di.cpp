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
#define mod 1000000007
#define N1 1005
#define sqr(x) ((x)*(x))%mod
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
ll dp1[N], dp2[N], dp3[N], dp4[N], val[N], cmp[N];
struct T{
  ll a, b, c;
  T (){}
  T(ll a, ll b, ll c) : a(a), b(b), c(c){}
  inline void clear(){
    a=0, b=0, c=0;
  }
};

struct ST{
  ll n;
  T lazy[4*N];
  ll tree[4*N];
  inline ll Op(ll &val1, ll &val2){
    return (val1+val2+mod)%mod;
  }
  inline ll unir(ll &a, ll &b){
    return ((a*b)%mod+mod)%mod;
  }
  inline T goes(T &laz, ll ta){
    T ty;
    ll a=laz.a, b=laz.b, c=laz.c;
    ll x, y, z;
    x=unir(val[ta], a)+(unir(b, dp4[ta]))%mod;
    x=(x+(unir(ta, c)*dp4[ta])%mod+mod)%mod;
    y=(unir(b,val[ta])+(2*c*dp4[ta])%mod+mod)%mod;
    z=unir(c, val[ta]);
    ty.a=x, ty.b=y, ty.c=z;
    return ty;
  }
  inline ll go(T &laz, ll ta){
    ll val=unir(laz.a, dp1[ta])+unir(laz.b, dp2[ta]);
    val=(val+unir(laz.c, dp3[ta])+mod)%mod;
    return val;
  }
  inline void updatepro(T &laz, ll id, ll l, ll r){
    if(laz.a==0 && laz.b==0 && laz.c==0) return;
    ll ta=r-l;
    ll sum=go(laz, ta-1);
    tree[id]=Op(tree[id], sum);
    lazy[id].a=Op(lazy[id].a, laz.a);
    lazy[id].b=Op(lazy[id].b, laz.b);
    lazy[id].c=Op(lazy[id].c, laz.c);
  }
  inline void proh(ll id, ll l, ll r){
    ll mid=(l+r)>>1, ta=mid-l;
    updatepro(lazy[id], id<<1, l, mid);
    T laz=goes(lazy[id], ta);
    updatepro(laz, id<<1|1, mid, r);
    lazy[id].clear();
  }
  inline void updateRange(ll x, ll y, T &val, ll id, ll l, ll r){
    if(x>=r || y<=l) return;
    if(x<=l && r<=y){
      ll ta=l-x;
      T laz=goes(val, ta);
      updatepro(laz, id, l, r);
      return;
    }
    proh(id, l, r); ll mid=(l+r)>>1;
    updateRange(x, y, val, id<<1, l, mid);
    updateRange(x, y, val, id<<1|1, mid, r);
    tree[id]=Op(tree[id<<1], tree[id<<1|1]);
  }
  inline ll query(ll x, ll y, ll id, ll l, ll r){
    if(x>=r || y<=l) return 0;
    if(x<=l && r<=y) return tree[id];
    proh(id, l, r); 
    ll left, right, mid=(l+r)>>1;
    left=query(x, y, id<<1, l, mid);
    right=query(x, y, id<<1|1, mid, r);
    return Op(left, right);
  }
  inline void build(){
    FER(i,0,4*n) lazy[i].clear();
    fill(tree,0);
  }
  inline void upd(ll x, ll y, T &val){
    updateRange(x, y, val, 1, 0, n);
  }
  inline ll que(ll x, ll y){
    return query(x, y, 1, 0, n);
  }
}st1,st2;

struct HLDES{
  ll n, gid;
  ll tsz[N], ar[N], rt[N];
  ll id[N], id1[N], d[N], p[N];
  vi adj[N], vr[N];
  inline ll dfs(ll u, ll pp, ll depth){
    p[u]=pp, d[u]=depth, tsz[u]=1;
    for(auto xd: adj[u]) if(xd!=pp) tsz[u]+=dfs(xd, u, depth+1);
    return tsz[u];  
  } 
  inline void make(){
    ll pe=dfs(0,-1, 0);
  }
  inline void go(ll u, ll root){
    id[u]=gid++, rt[u]=root;
    ll w=-1, bc=0;
    for(auto xd: adj[u]) if(xd!= p[u] && tsz[xd]>w) w=tsz[xd], bc=xd;
    if(bc) go(bc, root);
    for(auto xd: adj[u]) if(xd!=p[u] && xd!=bc) go(xd, xd);  
  }
  inline ll lca(ll a, ll b){
    while(rt[a]!=rt[b]){
      if(d[rt[a]]<d[rt[b]]) b=p[rt[b]];
      else a=p[rt[a]];
    }
    return d[a]>d[b]? b:a;
  }
  inline void goes(){
    FER(i,0,n) vr[rt[i]].pb(i);
    FER(i,0,n){
      if(sz(vr[i])) for(auto xd: vr[i]){
        id1[xd]=id[i]+sz(vr[i])-(d[xd]-d[i])-1;
      }
    }
  }
  inline void upd(ll a1, ll d1, ll a2, ll d2, ll u, ll v){
    ll a, b, c, node=lca(u,v);
    a=st1.unir(a1, a2);
    b=(st1.unir(a1, d2)+st1.unir(d1,a2)+mod)%mod;
    c=st1.unir(d1, d2);
    T laz, cur; 
    laz.a=a, laz.b=b, laz.c=c;
    ll l, r, x=u, y=v, ta, tx=d[u]-d[node];
    while(u!=-1){
      if(rt[u]==rt[node]){
        l=id1[u], r=id1[node];
        ta=d[x]-d[u];
        cur=st1.goes(laz, ta); 
        st1.upd(l,r,cur);
        u=-1;
      }
      else{
        l=id1[u], r=id1[rt[u]]+1;
        ta=d[x]-d[u];
        cur=st1.goes(laz, ta);
        st1.upd(l,r,cur);
        u=p[rt[u]];
      }
    }
    while(v!=-1){
      if(rt[v]==rt[node]){
        l=id[node], r=id[v]+1;
        ta=tx;
        cur=st2.goes(laz,ta);
        st2.upd(l,r,cur);
        ll gg=st2.que(l,r);
        v=-1;
      }
      else{
        l=id[rt[v]], r=id[v]+1;
        ta=tx+d[rt[v]]-d[node];
        cur=st2.goes(laz, ta);
        st2.upd(l,r,cur);
        ll gg=st2.que(l,r);
        v=p[rt[v]];
      }
    }
  }
  inline void que(ll &u, ll &v){
    ll ans=0, l, r;
    while(rt[u]!=rt[v]){
      if(d[rt[u]]<d[rt[v]]){
        l=id[rt[v]], r=id[v]+1;
        ans=(ans+st2.que(l,r)+mod)%mod;
        l=id1[v], r=id1[rt[v]]+1;
        ans=(ans+ st1.que(l,r)+mod)%mod;
        v=p[rt[v]];
      }
      else{
        l=id[rt[u]], r=id[u]+1;
        ans=(ans+st2.que(l,r)+mod)%mod;
        l=id1[u], r=id1[rt[u]]+1;
        ans=(ans+st1.que(l,r)+mod)%mod;
        u=p[rt[u]];
      }
    }
    if(d[u]<d[v]){
      l=id[u], r=id[v]+1;
      ans=(ans+st2.que(l,r)+mod)%mod;
      l=id1[v], r=id1[u]+1;
      ans=(ans+st1.que(l,r)+mod)%mod;
    }
    else{
      l=id[v], r=id[u]+1;
      ans=(ans+st2.que(l,r)+mod)%mod;
      l=id1[u], r=id1[v]+1;
      ans=(ans+st1.que(l,r)+mod)%mod;
    }
    cout<<ans<<endl;
  }
  inline void build(){
    gid=0;
    make();
    go(0,0);
    goes();
    st1.n=n; st2.n=n;
  }
}hld;
inline void build(ll r){
  FER(i,0,N-5) {
    cmp[i]=(i==0)? 0: (i*i)%mod;
    val[i]=(i==0)? 1 : (val[i-1]*r)%mod;
    dp1[i]=(i==0)? val[i] : (dp1[i-1]+val[i]+mod)%mod;
    dp2[i]=(i==0)? 0 : (dp2[i-1]+st1.unir(i,val[i])+mod)%mod;
    dp3[i]=(i==0)? 0 : (dp3[i-1]+st1.unir(cmp[i],val[i])+mod)%mod;
    dp4[i]=(i==0)? 0: (i*val[i])%mod;
  }
}
int main(){
  fastio;
  ll n, r; cin>>n>>r;
  build(r);
  ll a,b; hld.n=n;
  FER(i,0,n-1){
    cin>>a>>b; a--; b--;
    hld.adj[a].pb(b);
    hld.adj[b].pb(a);
  }
  hld.build();
  ll u, q, a1, d1, a2, d2 ;
  cin>>u>>q;
  FER(i,0,u){
    cin>>a1>>d1>>a2>>d2>>a>>b;
    a--; b--;
    hld.upd(a1,d1,a2,d2,a,b);
  }
  FER(i,0,q){
    cin>>a>>b; a--; b--;
    hld.que(a,b);
  }
  return 0;
}