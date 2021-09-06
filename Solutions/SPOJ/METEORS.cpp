// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define REP(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 300100
using namespace std;
typedef unsigned long long ll;
typedef pair<int,int> ii;

ll L[N],R[N];
ll own[N],req[N];
vector<int> sec[N];
vector<int> check[N];

struct STree{
  int n;
  ll t[2*N];
  STree(int n) : n(n){ REP(i,0,2*N) t[i] = 0; }
  void clear(){ REP(i,0,2*N) t[i] = 0; }
  void update(int l, int r, ll x){
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
      if(l&1) t[l++] += x;
      if(r&1) t[--r] += x;
    }
  }
  ll query(int p){
    ll ans = 0;
    for(p += n; p > 0; p >>= 1) ans += t[p];
    return ans;
  }
};

bool valid(int id, STree &st){
  ll sum = 0;
  for(int x : sec[id]){
    sum += st.query(x);
  }
  return sum >= req[id];
}

int main(){

  fastio;
  int n,m;
  cin >> n >> m;
  STree st(m+5);
  REP(i,1,m+1){
    cin >> own[i];
    sec[own[i]].pb(i);
  }
  REP(i,1,n+1) cin >> req[i];

  int k,l,r,x;
  cin >> k;
  vector< tuple<int,int,int> > query(k);
  for(int i = 0; i < k; ++i){
    cin >> l >> r >> x;
    query[i] = make_tuple(l,r,x);
  }

  for(int i = 1; i <= n; ++i){
    L[i] = 0;
    R[i] = k+1;
  }

  for(int it = 0; it < 22; ++it){
    st.clear();
    REP(i,0,k+1) check[i].clear();
    for(int i = 1; i <= n; ++i){
      if(L[i]+1 != R[i]){
        int mid = (L[i]+R[i])/2;
        check[mid].pb(i);
      }
    }
    for(int i = 0; i < k; ++i){
      tie(l,r,x) = query[i];
      if(l <= r){
        st.update(l,r+1,x);
      }else{
        st.update(l,m+1,x);
        st.update(1,r+1,x);
      }
      for(int x : check[i+1]){
        if(valid(x,st)) R[x] = i+1;
        else L[x] = i+1;
      }
    }
  }

  for(int i = 1; i <= n; ++i){
    if(R[i] == k+1) cout << "NIE" << endl;
    else cout << R[i] << endl;
  }

  return 0;
}
