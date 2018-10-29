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

struct node{
  ll l, r, d;
  vi v;
  node(){}
  node(ll l, ll r, ll d) : l(l), r(r), d(d){}
  inline void clear(){
    l=0, r=0, d=0;
    v.clear();
  }
};

struct Kruskal{
  ll n, id[N], val[N];
  set<ll> s[N];
  vector<tri> v;
  inline void build(){
    FER(i,0,n) s[i].clear();
    FER(i,0,n) id[i]=i, s[i].insert(val[i]);
  }
  inline ll find(ll a){
    while(id[a]!=a) id[a]=id[id[a]], a=id[a];
    return a;
  }
  inline void unir(ll x, ll y){
    ll p=find(x), q=find(y);
    ll nod1=id[p], nod2=id[q];
    if(sz(s[nod1])>sz(s[nod2])){
      for(auto xd: s[nod2]) s[nod1].insert(xd);
      id[q]=id[p];
    }
    else {
      for(auto xd: s[nod1]) s[nod2].insert(xd);
      id[p]=id[q];
    }
  }
  inline ll go(ll l, ll r, ll j){
    ll idx=sz(v)-1;
    FER(i,j,sz(v)){
      ll w=v[i].tm1, a=v[i].tm2, b=v[i].tm3;
      ll p1=find(a), p2=find(b);
      if(w>=r) {idx=i; break;}
      if(p1!=p2) unir(a, b);
    }
    return idx;
  }
};
ll ans[N];
tri queries[N];
int main(){
  fastio;
  ll n, m, k; cin>>n>>m>>k;
  Kruskal kr; kr.n=n;
  FER(i,0,n) cin>>kr.val[i];
  FER(i,0,m){
    ll a, b, c; cin>>a>>b>>c;
    a--; b--;
    kr.v.pb({c, {a, b}});
  }
  sort(all(kr.v)); kr. build();
  FER(i,0,k){
    ll a, b, c; cin>>a>>b>>c;
    a--; b--;
    queries[i]={c,{a, b}};
  }
  node cur, cur1, cur2;
  cur.l=0, cur.r=1e9+1, cur.d=0;
  FER(i,0,k) cur.v.pb(i);
  queue<node> q;
  q.push(cur); cur.clear();
  ll ni=-1, nn=0;
  while(sz(q)){
    cur=q.front(); q.pop();
    if(cur.d!=ni) kr.build(), ni=cur.d, nn=0;
    ll mid=(cur.l+cur.r)>>1;
    nn=kr.go(cur.l, mid, nn);
    if(cur.l+1==cur.r){
      nn=kr.go(mid, cur.r, nn);
      for(auto xd: cur.v){
        ll a=queries[xd].tm2, b=queries[xd].tm3;
        ll w=queries[xd].tm1;
        ll p1=kr.find(a), p2=kr.find(b);
        (p1==p2 && sz(kr.s[p1])>=w)? ans[xd]=mid: ans[xd]=-1;
      }
      continue;
    }
    for(auto xd: cur.v){
      ll a=queries[xd].tm2, b=queries[xd].tm3;
      ll w=queries[xd].tm1;
      ll p1=kr.find(a), p2=kr.find(b);
      (p1==p2 && sz(kr.s[p1])>=w)? cur1.v.pb(xd): cur2.v.pb(xd);
    }
    cur1.l=cur.l, cur1.r=mid, cur1.d=cur.d+1;
    cur2.l=mid, cur2.r=cur.r, cur2.d=cur.d+1;
    if(sz(cur1.v)) q.push(cur1);
    if(sz(cur2.v)) q.push(cur2);
    nn=kr.go(mid, cur.r, nn);
    cur.clear(), cur1.clear(), cur2.clear();
  }
  FER(i,0,k) cout<<ans[i]<<endl;
  return 0;
}