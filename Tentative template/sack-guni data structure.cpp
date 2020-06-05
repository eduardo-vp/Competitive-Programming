//sack+st, offline
//notar el update del add para mantener la estructura
//numero de colores diferentes de un subtree
struct ST{
  ll n;
  ll t[2*N];
  inline ll Op(ll &val1, ll &val2){
    if(val1<1) val1=0;
    if(val2<1) val2=0;
    return val1+val2;
  }
  inline void build(){
    IFR(i,n-1, 1) t[i]=Op(t[i<<1], t[i<<1|1]);
  }
  inline void modify(ll p, ll val){
    for(t[p+=n]+=val; p>>=1;) t[p]=Op(t[p<<1], t[p<<1|1]); 
  }
  inline ll que(ll l, ll r){
    ll ansl=0, ansr=0;
    for(l+=n,r+=n; l<r; l>>=1,r>>=1){
      if(l&1) ansl=Op(ansl, t[l++]);
      if(r&1) ansr=Op(t[--r], ansr);
    }
    return Op(ansl, ansr);
  }
} st;

ll tsz[N], can[N], cnt[N], col[N], d[N], big[N],froz[N];
vi adj[N];

inline ll make(ll u, ll pa, ll de){
  d[u]=de; tsz[u]=1;
  for(auto xd: adj[u]) if(xd!=pa) tsz[u]+=make(xd,u,de+1);
  return tsz[u];
}

inline void add(ll v, ll p, ll x){
  st.modify(cnt[col[v]],-abs(x));
  cnt[col[v]]+=x;
  st.modify(cnt[col[v]],abs(x));
  for(auto xd: adj[v]) if(xd!=p && !big[xd]) add(xd,v,x);
}

inline void go(ll v, ll p, ll x){
  ll mx=-1, bc=-1;
  for(auto xd: adj[v]) if(tsz[xd]>mx && xd!=p) mx=tsz[xd], bc=xd;
  for(auto xd: adj[v]) if(xd!=bc && xd!=p) go(xd,v,0);
  if(bc!=-1) go(bc, v ,1), big[bc]=1;
  add(v,p,1);
  froz[v]=st.que(1,1e5+1);
  if(bc!=-1) big[bc]=0;
  if(x==0) add(v,p,-1);
}
ll cc[N];
int main(){
  fastio;
  ll n,m,rt; cin>>n>>m>>rt; rt--;
  FER(i,0,n-1){
    ll a,b; cin>>a>>b; a--; b--;
    adj[a].pb(b), adj[b].pb(a);
  }
  map<ll,ll > m1; ll k=1;
  FER(i,0,n) cin>>cc[i],m1[cc[i]];
  for(auto &xd: m1) m1[xd.ff]=k++;
  FER(i,0,n) col[i]=m1[cc[i]];
  ll xd=make(rt,-1,1);
  st.n=1e5+1;
  vi ands;
  FER(i,0,m){
    ll x; cin>>x;x--;
    ands.pb(x);
  }
  go(rt,-1,1);
  FER(i,0,m) cout<<froz[ands[i]]<<endl;
  return 0;
}