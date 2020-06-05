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
#define sz(x) int(x.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)

#define N 200005
#define mod 998244353
#define N1 5
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

const int maxp = 1e6 + 1, maxv = 25, maxc = (int)1e4 + 1;
int ptot, pr[maxp], d[maxp], cnt;
ll p[maxc];
inline ll mod_add(ll x, ll y, ll p) {
  return (x += y) < p ? x : x - p;
}
inline ll mod_mul(ll x, ll y, ll p) {
  ll ret = x * y - (ll)((long double)x * y / p + 0.5) * p;
  return ret < 0 ? ret + p : ret;
}
inline ll mod_pow(ll x, ll k, ll p) {
  ll ret = 1 % p;
  for( ; k > 0; k >>= 1, x = mod_mul(x, x, p))
    (k & 1) && (ret = mod_mul(ret, x, p));
  return ret;
}
bool miller_rabin(ll n) {
  if(n == 2) return 1;
  if(n < 2 || !(n & 1))
    return 0;
  ll s = 0, r = n - 1;
  for( ; !(r & 1); r >>= 1, ++s);
  for(int i = 0; pr[i] < n && pr[i] < maxv; ++i) {
    ll cur = mod_pow(pr[i], r, n), nxt;
    for(int j = 0; j < s; ++j) {
      nxt = mod_mul(cur, cur, n);
      if(nxt == 1 && cur != 1 && cur != n - 1) return 0;
      cur = nxt;
    }
    if(cur != 1) return 0;
  }
  return 1;
}
inline ll gcd(ll a, ll b) {
  int ret = 0;
  while(a) {
    for( ; !(a & 1) && !(b & 1); ++ret, a >>= 1, b >>= 1);
    for( ; !(a & 1); a >>= 1);
    for( ; !(b & 1); b >>= 1);
    if(a < b)
      swap(a, b);
    a -= b;
  }
  return b << ret;
}
inline ll pollard_rho(ll n) {
  static ll seq[maxp];
  while(1) {
    ll x = rand() % n, y = x, c = rand() % n;
    ll *px = seq, *py = seq, tim = 0, prd = 1;
    while(1) {
      *py++ = y = mod_add(mod_mul(y, y, n), c, n);
      *py++ = y = mod_add(mod_mul(y, y, n), c, n);
      if((x = *px++) == y) break;
      ll tmp = prd;
      prd = mod_mul(prd, abs(y - x), n);
      if(!prd) return gcd(tmp, n);
      if((++tim) == maxv) {
        if((prd = gcd(prd, n)) > 1 && prd < n) return prd;
        tim = 0;
      }
    }
    if(tim && (prd = gcd(prd, n)) > 1 && prd < n) return prd;
  }
}
inline void decompose(ll n) {
  for(int i = 0; i < cnt; ++i)
    if(n % p[i] == 0) {
      p[cnt++] = p[i];
      n /= p[i];
    }
  if(n < maxp) {
    for( ; n > 1; p[cnt++] = d[n], n /= d[n]);
  } else if(miller_rabin(n)) {
    p[cnt++] = n;
  } else {
    ll fact = pollard_rho(n);
    decompose(fact), decompose(n / fact);
  }
}
inline void build(){
  FER(i, 2, maxp) {
    if(!d[i]) pr[ptot++] = d[i] = i;
    for(int j = 0, k; (k = i * pr[j]) < maxp; ++j) {
      d[k] = pr[j];
      if(d[i] == pr[j]) break;
    }
  }   
} 
inline void construct(vii &v){
  sort(p, p+cnt);
  for(int i = 0; i < cnt; ) {
    ll ctr=0;
    for(ll pp = p[i]; i < cnt && p[i] == pp; ++i, ++ctr);
    v.pb({p[i-1], ctr});
  }
  cnt=0;
}
inline void make(ll n){
  decompose(n);
}


int main(){
  build();
  ll n; cin>>n;
  make(n);
  vii v; construct(v);
  for(auto xd: v) trace(xd.ff, xd.ss); 
  return 0;
}
