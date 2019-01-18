
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
// #define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
 
#define N 200005
#define mod 30011
#define N1 105
#define sqr(x) (x)*(x)
#define INF 2000000000000000000 
#define pi acos(-1);
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

inline ll bp(ll a, ll n){
    if(n==0) return 1;
    if(n&1) return (a*bp(a, n-1))%mod;
    ll x=bp(a, n>>1);
    return (sqr(x)%mod+mod)%mod;
}

// Fast Walsh-Hadamard Transform for xor multiplication
// take note about the matrix associated
// |+1 +1|
// |+1 -1|
// The inverse is the same as the matrix, so it's not necesary
// to have a bool parameter in the convolution

struct FWHTXor{
    ll n;
    inline void GetInverse(vi &v){
        n=1;
        while(n<sz(v)) n<<=1;
        v.resize(n);
        for(ll len=1; (len<<1)<=n; len<<=1){
            for(ll i=0; i<n; i+=(len<<1)){
                FER(j,0,len){
                    ll a=v[i+j], b=v[i+j+len];
                    v[i+j]=(a+b)%mod;
                    v[i+j+len]=(mod+a-b)%mod;
                }
            }
        }
    }
}fwht;
int main(){
    fastio;
    ll n, k; cin>>n>>k;
    vi v;
    FER(i,0,k+1) v.pb(1);
    fwht.GetInverse(v);
    FER(i,0,fwht.n) v[i]=bp(v[i], n);
    fwht.GetInverse(v);
    ll inv=bp(fwht.n, mod-2), ans=0;
    FER(i,1,fwht.n){
        ans+=(v[i]*inv)%mod;
        ans%=mod;
    }
    cout<<ans<<endl;
    return 0;
}
