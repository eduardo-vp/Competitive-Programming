
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
#define M 26
#define bas 31
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

struct NTT{
    ll root_1, root, root_pw;
    inline ll bp(ll a, ll b){
        if(b==0) return 1;
        if(b&1) return (a*(bp(a, b-1)))%mod;
        ll x=bp(a, b>>1)%mod;
        x=(x+mod)%mod;
        return ((x*x)%mod+mod)%mod;;
    }
    inline ll inverse(ll a){
        return bp(a, mod-2);
    }
    inline void build(){
        // Si:c*pow(2, k)+1=mod
        // Entonces root cumple:
        // pow(root, 1<<(pow(2, k))=1mod
        // Mejor complejidad=Primary root test.
        root_pw=1<<23;
        FER(i,2,1e5+1) if(bp(i, root_pw)==1){ root=i; break;}
        root_1=inverse(root);
    }
    inline void fft(vi &a , bool inv){
        ll n=sz(a);
        for(ll i=1, j=0; i<n; i++){
            ll bt=n>>1;
            for(; j&bt; bt>>=1) j^=bt;
            j^=bt;
            if(i<j) swap(a[i], a[j]);
        }
        for(ll len=2; len<=n; len<<=1){
            ll wlen=inv? root_1: root;
            for(ll i=len; i<root_pw; i<<=1) wlen=(sqr(wlen)%mod+mod)%mod;
            for(ll i=0; i<n; i+=len){
                ll w=1;
                for(ll j=0; j<len/2; j++){
                    ll u=a[i+j], v=(a[i+j+len/2]*w)%mod;
                    a[i+j]=u+v<mod? u+v: u+v-mod;
                    a[i+j+len/2]=u-v>=0? u-v: u-v+mod;
                    w=((w*wlen)%mod+mod)%mod;
                }
            }
        }
        if(inv){
            ll n_1=inverse(sz(a));
            for(auto &xd: a) xd=((xd*n_1)%mod+mod)%mod;
        }
    }
    inline vi GetConvolution(vi a, vi b){
        ll n=1;
        while(n<sz(a)+sz(b)) n<<=1;
        a.resize(n), b.resize(n);
        fft(a, false), fft(b, false);
        FER(i,0,n) a[i]=((a[i]*b[i])%mod+mod)%mod;
        fft(a, true);
        return a;
    }
    inline vi BinPolyExp(vi &a, ll b){
        if(b==1) return a;
        ll n=1;
        while(n<sz(a)*b) n<<=1;
        a.resize(n);
        fft(a, false);
        for(auto &xd: a) xd=bp(xd, b);
        fft(a, true);
        return a;
    }
}ntt;


int main(){
    fastio;
    NTT ntt;
    ntt.build();
    ll n, k; cin>>n>>k;
    vi v(10);
    FER(i,0,k){
        ll x; cin>>x;
        v[x]=1;
    }
    ll ans=0;
    vi froz=ntt.BinPolyExp(v, n/2);
    for(auto xd: froz) ans=(ans+sqr(xd))%mod;
    ans=(ans+mod)%mod;
    cout<<ans<<endl;
    return 0;
}
