 
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
 
#define N 100050
#define mod 1000000007
#define N1 450
#define sqr(x) (x)*(x)
#define INF 2000000000
 
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
// -----------------------------Mo on trees------------------------------ 
// note that there are 2 cases, in all of them we need nodes with one occurence 
// in the range of the eulerian path of the tree.
// Consider path from a to b, with be[i]: start time and en[i] the end time in
// the simple dfs (here's solve)
// Case 1: LCA(a, b)= (a || b) just matter a and b
// Query = (l, r) -> be[a], be[b]+1
// Case 2: u = LCA(a, b) != (a || b), u occurs 2 times, so we need to take 
// it in mind as an special case
// Query = (l, r) -> (en[a], ,be[b]+1)
// example of COT2, spoj solution.

vi adj[N];
ll be[N], en[N], tsz[N], val[N], p[N], id[N], rt[N], ar[N], d[N], t[N], pos, gid;
 
inline ll solve(ll u, ll pp, ll depth){
    be[u]=pos, ar[pos++]=u, tsz[u]=1, p[u]=pp, d[u]=depth;
    for(auto xd: adj[u]) if(xd!=pp) tsz[u]+=solve(xd, u, depth+1);
    en[u]=pos, ar[pos++]=u;
    return tsz[u];
}
 
inline void go(ll u, ll root){
    rt[u]=root, id[u]=gid++;
    ll w=-1, bc=0;
    for(auto xd: adj[u]) if(xd!=p[u] && w<tsz[xd]) w=tsz[xd], bc=xd;
    if(bc) go(bc, root);
    for(auto xd: adj[u]) if(xd!=p[u] && xd!=bc) go(xd, xd);    
}
 
inline ll lca(ll a, ll b){
    while(rt[a]!=rt[b]) d[rt[a]]>d[rt[b]]? a=p[rt[a]]: b=p[rt[b]];
    return d[a]>d[b]? b: a;
}
 
struct Range{
    vector<tri> v, v1;
    Range(){}
    Range(vector<tri> &v, vector<tri> &v1): v(v), v1(v1){}
}rn[N1];
 
struct Mo{
    ll n, m;
    vector<tri> v;
    ll ans[N], vis[N], can[N], froz[N];
    inline void Construct(){
        ll l, r, id;
        m=sqrt(n);
        sort(all(v));
        FER(i,0,sz(v)) rn[v[i].tm1/m].v.pb(v[i]);
        m+=2;
        fill(vis, 0), fill(can, 0), fill(froz, 0), fill(ans, 0);
        FER(i,0,m){
            FER(j, 0, sz(rn[i].v)){
                l=rn[i].v[j].tm1;
                r=rn[i].v[j].tm2;
                id=rn[i].v[j].tm3;
                rn[i].v1.pb({r, {l, id}});
            }
            sort(all(rn[i].v1));
        }
    }
    inline void Add(ll i, ll id){
        vis[ar[i]]++;
        ll cur;
        if(vis[ar[i]]==2){
            cur=ar[i];
            can[val[cur]]--;
            if(can[val[cur]]==0) ans[id]--;
        }
        if(vis[ar[i]]==1){
            cur=ar[i];
            can[val[cur]]++;
            if(can[val[cur]]==1) ans[id]++;
        }
    }
    inline void Rem(ll i, ll id){
        vis[ar[i]]--;
        ll cur;
        if(vis[ar[i]]==1){
            cur=ar[i];
            can[val[cur]]++;
            if(can[val[cur]]==1) ans[id]++;
        }
        if(vis[ar[i]]==0){
            cur=ar[i];
            can[val[cur]]--;
            if(can[val[cur]]==0) ans[id]--;
        }
    }
    inline void build(){
        ll l, r, id;
        ll curL=0, curR=0, valor=0, nod, nod1, nod2, flag;
        FER(i,0,m){
            FER(j, 0, sz(rn[i].v1)){
                l=rn[i].v1[j].tm2;
                r=rn[i].v1[j].tm1;
                id=rn[i].v1[j].tm3;
                nod1=ar[l], nod2=ar[r-1];
                nod=lca(nod1, nod2);
                flag=1;
                if(nod==nod1 || nod==nod2) flag=0;
                ans[id]=valor;
                while(curL<l) Rem(curL++, id);
                while(curL>l) Add(--curL, id);
                while(curR>r) Rem(--curR, id);
                while(curR<r) Add(curR++, id);
                if(flag && can[val[nod]]==0LL) froz[id]=1;
                valor=ans[id];
            }
        }
    }
}mo;
 
inline void clear(ll n){
    FER(i,0,n) {
        adj[i].clear();
        be[i]=0;
        en[i]=0;
        tsz[i]=0;
        d[i]=0;
        p[i]=0;
        val[i]=0;
        rt[i]=0;
        id[i]=0;
        ar[i]=0;
        t[i]=0;
    }
}
int main(){
    fastio;
    ll n, m; 
    while(cin>>n>>m){
        clear(n);
        pos=0, gid=0;
        map<ll, ll > mp;
        FER(i,0,n) cin>>t[i], mp[t[i]];
        for(auto xd: mp) mp[xd.ff]=pos++;
        FER(i,0,n) val[i]=mp[t[i]];
        pos=0;
        FER(i,0,n-1){
            ll a, b; cin>>a>>b; a--; b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        solve(0, -1, 0);
        go(0, 0);
        mo.n=n<<1;
        ll l, r, u, v, nod;
        FER(i,0,m){
            cin>>u>>v; u--; v--;
            nod=lca(u, v);
            l=be[u], r=be[v];
            if(l>r) swap(u, v);
            if(nod==u || nod==v) l=be[u], r=be[v];
            else l=en[u], r=be[v];
            r++;
            mo.v.pb({l, {r, i}});
        }
        mo.Construct(); 
        mo.build();
        FER(i,0,m) cout<<mo.ans[i]+mo.froz[i]<<endl;
    }
    return 0;
}