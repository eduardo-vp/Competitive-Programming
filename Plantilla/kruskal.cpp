struct Kruskal{
  ll id[N], n, ans;
  vector<pair<ll,ii>> v;
  vii adj[N];
  inline void build(){
    FER(i,0,n) id[i]=i;
  }
  inline ll find(ll x){
    while(id[x]!=x) id[x]=id[id[x]], x=id[x];
    return x;
  }
  inline void unir(ll x, ll y){
    ll p=find(x), q=find(y);
    id[p]=id[q];
  }
  inline void clear(){
    fill(id,0);
    ans=0;
  }
  inline void go(ll l, ll r){
    FER(i,l,r){
     ll w=v[i].tm1, x=v[i].tm2, y=v[i].tm3;
     if(find(x)!=find(y)) ans+=w, unir(x,y),adj[x].pb({y,w}), adj[y].pb({x,w});
   }
  }
};