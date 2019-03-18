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
 
#define N 6800015
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
// -----------------------------Mo on trees------------------------------ 
// note that there are 2 cases, in all of them we need nodes with one occurence 
// in the range of the eulerian path of the tree.
// Consider path from a to b, with be[i]: start time and en[i] the end time in
// the simple dfs 
// Case 1: LCA(a, b)= (a || b) just matter a and b
// Query = (l, r) -> be[a], be[b]+1
// Case 2: u = LCA(a, b) != (a || b), u occurs 2 times, so we need to take 
// it in mind as an special case
// Query = (l, r) -> (en[a], ,be[b]+1)
// Note that Remove and Add operations are diferent for updates or queries
// example: ADAFTBLL, spoj solution.

vi adj[1<<18];
ll be[1<<18], en[1<<18], p[1<<18], rt[1<<18], d[1<<18], nodes[1<<18], value[1<<18], tsz[1<<18], pos;
 
inline void dfs(ll u, ll pp, ll depth){
    be[u]=pos, nodes[pos++]=u, tsz[u]=1, p[u]=pp, d[u]=depth;
    for(auto xd: adj[u]) if(xd!=pp) dfs(xd, u, depth+1), tsz[u]+=tsz[xd];
    en[u]=pos, nodes[pos++]=u;
}
 
inline void go(ll u, ll root){
    rt[u]=root;
    ll w=-1, bc=0;
    for(auto xd: adj[u]) if(xd!=p[u] && w<tsz[xd]) w=tsz[xd], bc=xd;
    if(bc) go(bc, root);
    for(auto xd: adj[u]) if(xd!=p[u] && xd!=bc) go(xd, xd);
}
 
inline ll lca(ll a, ll b){
    while(rt[a]!=rt[b]) d[rt[a]]>d[rt[b]]? a=p[rt[a]]: b=p[rt[b]];
    return d[a]>d[b]? b: a;
}
 
struct Que{
    ll l, r, t, id, lq, rq;
    Que(){}
    Que(ll l, ll r, ll t, ll id, ll lq, ll rq) : l(l), r(r), t(t), id(id), lq(lq), rq(rq){}
}Q[1<<18];
 
struct Upd{
    ll p, nod, last, nxt;
    Upd(){}
    Upd(ll p, ll nod, ll last, ll nxt) : p(p), nod(nod), last(last), nxt(nxt){} 
}U[1<<18];
 
struct MO{
    ll n, curR, curL, q, t, valor;
    ll ans[1<<18], ar[1<<18], cnt[1<<18], froz[1<<18], fre[1<<18];
    MO(){}
    inline void Add(ll val, ll cur){
        fre[val]++;
        if(fre[val]==2){
            cnt[cur]--;
            valor-=cnt[cur];
        }
        if(fre[val]==1){
            valor+=cnt[cur];
            cnt[cur]++;
        }
    }
    inline void Rem(ll val, ll cur){
        fre[val]--;
        if(fre[val]==1){
            valor+=cnt[cur];
            cnt[cur]++;
        }
        if(fre[val]==0){
            cnt[cur]--;
            valor-=cnt[cur];
        }
    }
    inline void RemUpd(ll nod, ll cur){
        if(fre[nod]==1){
            cnt[cur]--;
            valor-=cnt[cur];
        }
    }
    inline void AddUpd(ll nod, ll cur){
        if(fre[nod]==1){
            valor+=cnt[cur];
            cnt[cur]++;
        }
    }
    inline void Retime(ll i, ll nod, ll cur){
        if(i>=curL && i<curR){
            RemUpd(nod, ar[i]);
            AddUpd(nod, cur);
        }
        ar[i]=cur;
    }
    inline void Query(ll l, ll r, ll timer, ll id){
        ll nod1=nodes[l], nod2=nodes[r-1], nod=lca(nod1, nod2), flag=1;
        if(nod==nod1 || nod==nod2) flag=0;
        while(t<timer) Retime(U[t].p, U[t].nod, U[t].nxt), t++;
        while(t>timer) t--, Retime(U[t].p, U[t].nod, U[t].last);
        while(curR<r) Add(nodes[curR], ar[curR]), curR++;
        while(curL>l) curL--, Add(nodes[curL], ar[curL]);
        while(curL<l) Rem(nodes[curL], ar[curL]), curL++;
        while(curR>r) curR--, Rem(nodes[curR], ar[curR]);
        ll idx=be[nod];
        if(flag) froz[id]=cnt[ar[idx]];
        assert(froz[id]>=0);
        ans[id]=valor;
    }
    inline void build(){
        sort(Q, Q+q, [&](Que &a, Que &b){
            if(a.lq!=b.lq) return a.lq<b.lq;
            if(a.rq!=b.rq) return a.rq<b.rq;
            return a.t<b.t;
        }
        );
        curL=0, curR=0, valor=0LL;
        FER(i,0,q) Query(Q[i].l, Q[i].r, Q[i].t, Q[i].id);
    }
}mo;
 
 
 
int main(){
    fastio;
    ll n, q, add; cin>>n>>q;
    add=(ll) pow(n<<1, 2.0/3.0);
    FER(i,0,n) cin>>value[i];
    FER(i,0,n-1){
        ll a, b; cin>>a>>b; 
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(0, -1, 0);
    go(0, 0);
    mo.n=n<<1;
    FER(i,0,n<<1) mo.ar[i]=value[nodes[i]];
    ll type, l, r, u, v, t1=0, t2=0, nod;
    FER(i,0,q){
        cin>>type>>u>>v;
        if(type==2){
            nod=lca(u, v);
            l=be[u], r=be[v];
            if(l>r) swap(u, v);
            if(nod==u || nod==v) l=be[u], r=be[v];
            else l=en[u], r=be[v];
            r++;
            Q[t1]={l, r, t2, t1, l/add, (r-1)/add};
            t1++;
        }
        else{
            l=be[u], r=en[u];
            U[t2].p=l, U[t2].nxt=v, U[t2].nod=u;
            t2++;
            U[t2].p=r, U[t2].nxt=v, U[t2].nod=u;
            t2++;
        }
    }
    mo.q=t1, mo.t=t2;
    FER(i,0,t2){
        U[i].last=mo.ar[U[i].p];
        mo.ar[U[i].p]=U[i].nxt;
    }
    mo.build();
    FER(i,0,t1) {
        cout<<mo.ans[i]+mo.froz[i]<<endl;
    }
    return 0;
} 
