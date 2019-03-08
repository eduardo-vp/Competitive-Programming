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
#define INF 2000000000
#define mod 1000000007
#define bas 31
#define pi acos(-1) 
using namespace std;
using namespace __gnu_pbds;
typedef int ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii > tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> set_t;
#define trace(...) f(#__VA_ARGS__, __VA_ARGS__)
template<typename t> void f(const char* x, t&& val1){
    cout<<x<< " : "<<val1<<endl; }
template<typename t1, typename... t2> void f(const char* x, t1&& val1, t2&&... val2){
    const char* xd=strchr(x+1, ',');
    cout.write(x, xd-x)<<" : "<<val1<<" | ";
    f(xd+1, val2...); }

map<ll , ll> m;
ll z;
inline ll OnlineCom(ll x){
    return m.count(x)? m[x]: m[x]=++z;
}
 
struct Que{
    ll l, r, t, id, lq, rq;
    Que(){}
    Que(ll l, ll r, ll t, ll id, ll lq, ll rq) : l(l), r(r), t(t), id(id), lq(lq), rq(rq){}
}Q[1<<18];

struct Upd{
    ll p, last, nxt;
    Upd(){}
    Upd(ll p, ll last, ll nxt) : p(p), last(last), nxt(nxt){} 
}U[1<<18];

struct MO{
    ll n, curR, curL, q, t;
    ll ans[1<<18], ar[1<<18], cnt[1<<18], fre[1<<18];
    MO(){}
    inline void Add(ll val){
        fre[cnt[val]]--;
        fre[++cnt[val]]++;
    }
    inline void Rem(ll val){
        fre[cnt[val]]--;
        fre[--cnt[val]]++;
    }
    inline void Retime(ll i, ll cur){
        if(i>=curL && i<curR){
            Add(cur);
            Rem(ar[i]);
        }
        ar[i]=cur;
    }
    inline void Query(ll l, ll r, ll timer, ll id){
        while(t<timer) Retime(U[t].p, U[t].nxt), t++;
        while(t>timer) t--, Retime(U[t].p, U[t].last);
        while(curL<l) Rem(ar[curL++]);
        while(curL>l) Add(ar[--curL]);
        while(curR>r) Rem(ar[--curR]);
        while(curR<r) Add(ar[curR++]);
        ll mex=1;
        while(fre[mex++]);
        ans[id]=mex-1;
    }
    inline void build(){
        sort(Q, Q+q, [&](Que &a, Que &b){
            if(a.lq!=b.lq) return a.lq<b.lq;
            if(a.rq!=b.rq) return a.rq<b.rq;
            return a.t<b.t;
        }
        );
        curL=0, curR=0;
        FER(i,0,q) Query(Q[i].l, Q[i].r, Q[i].t, Q[i].id);
    }
}mo;
 
int main(){
    fastio;
    ll n, q, add; cin>>n>>q;
    add=(ll) pow(n, 2.0/3.0);
    mo.n=n;
    FER(i,0,n) {
        cin>>mo.ar[i];
        mo.ar[i]=OnlineCom(mo.ar[i]);
    }
    ll type, l, r, t1=0, t2=0;
    FER(i,0,q){
        cin>>type>>l>>r; l--;
        if(type==1){
            Q[t1]={l, r, t2, t1, l/add, (r-1)/add};
            t1++;
        }
        else{
            U[t2].p=l, U[t2].nxt=OnlineCom(r);
            t2++;
        }
    }
    mo.q=t1, mo.t=t2;
    FER(i,0,t2){
        U[i].last=mo.ar[U[i].p];
        mo.ar[U[i].p]=U[i].nxt;
    }
    mo.build();
    FER(i,0,t1) cout<<mo.ans[i]<<endl;
    return 0;
} 
