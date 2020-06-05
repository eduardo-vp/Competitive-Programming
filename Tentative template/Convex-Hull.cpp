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
typedef double T;
const T EPS = 1e-7;
struct PT { 
  T x, y; 
  PT() {} 
  PT(T x, T y) : x(x), y(y) {}
  bool operator<(const PT &rhs) const {
    return mp(y,x) < mp(rhs.y,rhs.x); 
  }
  bool operator==(const PT &rhs) const { 
    return mp(y,x) == mp(rhs.y,rhs.x);
  }
};
 
T cross(PT p, PT q) { return p.x*q.y-p.y*q.x; }
T area2(PT a, PT b, PT c) { 
  return cross(a,b) + cross(b,c) + cross(c,a); 
}
double dis(PT &a, PT &b){
  double l1=a.x-b.x,l2=a.y-b.y;
  return sqrt(l1*l1+l2*l2);
}
#ifdef REMOVE_REDUNDANT
bool between(const PT &a, const PT &b, const PT &c) {
  return (fabs(area2(a,b,c)) < EPS && 
       (a.x-b.x)*(c.x-b.x) <= 0 && 
       (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif
  //vector<PT> up, dn;
void ConvexHull(vector<PT> &pts) {
  sort(pts.begin(), pts.end());
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  vector<PT> up, dn;
  for (int i = 0; i < pts.size(); i++) {
    while (up.size() > 1 && 
      area2(up[up.size()-2], up.back(), pts[i]) >= 0) 
        up.pop_back();
    while (dn.size() > 1 && 
      area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0)
        dn.pop_back();
    up.push_back(pts[i]);
    dn.push_back(pts[i]);
  }
  pts = dn;
  for (int i = (int) up.size() - 2; i >= 1; i--) 
    pts.push_back(up[i]);
  
#ifdef REMOVE_REDUNDANT
  if (pts.size() <= 2) return;
  dn.clear();
  dn.push_back(pts[0]);
  dn.push_back(pts[1]);
  for (int i = 2; i < pts.size(); i++) {
    if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) 
      dn.pop_back();
    dn.push_back(pts[i]);
  }
  if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
    dn[0] = dn.back();
    dn.pop_back();
  }
  pts = dn;
#endif
 
}

int main(){
  fastio;
  vector<PT> v;
  ConvexHull(v);
  // antihorario desde el mas a la izquierda.
  return 0;
}