#include <bits/stdc++.h>
// #include <sys/resource.h>
#define pb push_back
#define ff  first
#define ss second
#define sz(x) ll(x.size())
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)

#define sqr(x) (x)*(x)
#define INF 200000000
#define N 6800005
using namespace std;

typedef int ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

#define trace(...) f(#__VA_ARGS__, __VA_ARGS__)
 
template<typename t> void f(const char* x, t&& val1){
    cout<<x<< " : "<<val1<<endl;
}
template<typename t1, typename... t2> void f(const char* x, t1&& val1, t2&&... val2){
    const char* xd=strchr(x+1, ',');
    cout.write(x, xd-x)<<" : "<<val1<<" | ";
    f(xd+1, val2...);
}

// ------------------------------- Persistent Onnline Trie ------------------------
// Persistent onnline trie based on persistent segment tree to mantain frecuency
// note that "the persistent" is build at the same time (trie and persistent)
// take care about the bound between trie and pst (N value)
// if roll back queries is no needed, it's not necesary to use pst
// i.e CF 706D

map<ll, ll> mts;
ll zz;

inline ll OC(ll kst){
  if(mts.count(kst)) return mts[kst];
  mts[kst]=zz++;
  return mts[kst];
}
struct Trie{
    ll nod;
    ll m[N][2];
    ll n, nodes;
    ll staL[N], staR[N], tree[N], ar[1<<18];
    vi tnt;
    inline ll Op(ll &val1, ll &val2){
        return val1+val2;
    }
  
    inline ll newParent(ll l, ll r){
        ll p=nodes++;
        staL[p]=l;
        staR[p]=r;
        tree[p]=Op(tree[l], tree[r]);
        return p;
    }
  
    inline ll newLeaf(ll val){
        ll p=nodes++;
        staL[p]=staR[p]=0;
        tree[p]=val;
        return p;
    }
  
    inline ll updR(ll p, ll add, ll id, ll l, ll r){
        if(l+1==r) return newLeaf(Op(tree[id], add));
        ll mid=(l+r)>>1;
        if(p<mid) return newParent(updR(p, add, staL[id], l, mid), staR[id]);
        else return newParent(staL[id], updR(p, add, staR[id], mid, r));
    }
  
    inline ll Query(ll x, ll y, ll id, ll l, ll r){
        if(x>=r || y<=l) return 0;
        if(x<=l && r<=y) return tree[id];
        ll mid=(l+r)>>1;
        ll left=Query(x, y, staL[id], l, mid), right=Query(x, y, staR[id], mid, r);
        return Op(left, right);
    }
  
    inline ll build1(ll l, ll r){
        ll mid=(l+r)>>1;
        if(r-l<2) return newLeaf(ar[l]);
        ll left=build1(l, mid), right=build1(mid, r);
        return newParent(left, right);
    }
  
    inline ll que(ll l, ll r, ll timer){
        return Query(l, r, timer, 0, n);
    }
  
    inline ll upd(ll p, ll add, ll timer){
        return updR(p, add, timer, 0, n);
    }
  
    inline ll build(){
        return build1(0, n);
    }

    inline ll AddTrie(ll last, ll i, ll val){
        ll rt=nod++;
        if(i<0) return rt;
        ll r=(val>>i)&1;
        m[rt][r^1]=m[last][r^1];
        m[rt][r]=AddTrie(m[last][r], i-1, val);
        return rt;
    }

    inline ll check(ll id){
      if(m[id][0]!=0 && m[id][1]!=0) return 1;
      return 0;
    }

    inline ii RemTrie(ll id, ll val, ll timerst){
      ll y=OC(val);
      ll rt=upd(y, -1, timerst), rx;
      ll cur=que(y, y+1, rt);
      ll rrt=id;
      if(!cur){
        rrt=AddTrie(id, 30, val);
        id=rrt;
        tnt.clear();
        IFR(i, 30, 0){
          ll r=(val>>i)&1;
          id=m[id][r];
          tnt.pb(id);
        }
        reverse(all(tnt));
        FER(i, 0, 31){
          ll r=(val>>i)&1, r1=tnt[i];
          if(check(r1) || i==30) {
            rx=(val>>(i-1))&1;
            m[r1][rx]=0;
            break;
          }
        }
      }
      return {rt, rrt};
    }

    inline ll QueryMax(ll id, ll val){
        ll ans=0;
        IFR(i,30,0){
          ll r=(val>>i)&1;
          if(m[id][r ^ 1]) id=m[id][r ^ 1], ans+=((r^1)<<i);
          else id=m[id][r], ans+=(r<<i);
        }
        return ans ^ val;
    }

}st;

int main(){
  fastio;
  ll q; cin>>q;
  st.n=q, st.nodes=0, st.nod=1;
  FER(i,0,st.n) st.ar[i]=0;
  ll rst, rtr;
  rst=st.build();
  rtr=st.AddTrie(0, 30, 0);
  char s;
  ll a, x;
  ii cur;
  FER(i,0,q){
    cin>>s;
    if(s=='+'){
      cin>>x;
      rtr=st.AddTrie(rtr, 30, x);
      a=OC(x);
      rst=st.upd(a, 1, rst);  
    }
    else if(s=='-'){
      cin>>x;
      cur=st.RemTrie(rtr, x, rst);
      rst=cur.ff;
      rtr=cur.ss;
    }
    else{
      cin>>x;
      a=st.QueryMax(rtr, x);
      cout<<a<<endl;
    }
  }
  return 0;
}
