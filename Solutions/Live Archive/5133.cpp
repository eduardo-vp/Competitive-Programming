/*
  Convex Hull Trick
*/
// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { 
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return 1.0 * (x->b - y->b)*(z->m - y->m) >= 1.0 * (y->b - z->b)*(y->m - x->m);
    }
    void add(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll query(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};

ll n,c,d;
vector<pair<ii,ii>> vec;
HullDynamic lc;

int main(){

  int tc = 1;
  while(scanf("%lld %lld %lld",&n,&c,&d)){
    if(n == 0 and c == 0 and d == 0) break;
    lc.clear();
    lc.add(0,c);
    vec.resize(n);
    printf("Case %d: ",tc++);
    FER(i,0,n) scanf("%lld %lld %lld %lld",&vec[i].ff.ff,&vec[i].ff.ss,&vec[i].ss.ff,&vec[i].ss.ss);
    sort(vec.begin(),vec.end());
    for(int i = 0; i < n; ){
      vector<ii> lines;
      do{
        ll d = vec[i].ff.ff, p = vec[i].ff.ss, r = vec[i].ss.ff, g = vec[i].ss.ss;
        ll best = lc.query(d-1);
        if(best >= p){
          ll a = d, b = best - p + r;
          lines.pb(ii(g,b-g*a));
        }
        i++;
      }while(i < n and vec[i].ff.ff == vec[i-1].ff.ff);
      for(ii p : lines) lc.add(p.ff,p.ss);
    }
    printf("%lld\n",lc.query(d));
  }

  return 0;
}
