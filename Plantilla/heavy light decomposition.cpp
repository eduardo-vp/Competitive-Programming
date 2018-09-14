struct HLDES{
  ll n, gid;
  ST st1, st2;
  vii adj[N];
  vi v[N];
  ll id[N], id1[N];
  ll p[N], tsz[N], ar[N], rt[N], d[N], val[N];
  inline ll dfs(ll u, ll pp, ll depth, ll w) {
    p[u]=pp, d[u]=depth, tsz[u]=1, val[u]=w;
    for(auto xd: adj[u]) if(xd.ff != pp) tsz[u]+=dfs(xd.ff, u, depth+1, xd.ss);
    return tsz[u];
  }
  inline void make(){
    ll pe=dfs(0, -1, 0, -MAXN);// neutro
  }
  inline void go(ll u, ll root){
    ar[gid]=val[u];
    id[u]=gid++, rt[u]=root;
    ll w=-1, bc=0;
    for(auto xd: adj[u]) if(xd.ff!=p[u] && tsz[xd.ff]>w) bc=xd.ff, w=tsz[xd.ff];
    if(bc) go(bc,root);
    for(auto xd:adj[u]) if(xd.ff!=p[u] && xd.ff!=bc) go(xd.ff, xd.ff);  
  }
  inline void goes(){
    FER(i,0,n) v[rt[i]].pb(i);
    FER(i,0,n){
      if(sz(v[i])){
        for(auto xd:v[i]){
          id1[xd]=id[i]+sz(v[i])-(d[xd]-d[i])-1;
        }
      }
    }
  }
  inline ll lca(ll u, ll v){
    while(rt[u]!=rt[v]){
      if(d[rt[u]]<d[rt[v]]) v=p[rt[v]];
      else u=p[rt[u]];
    }
    return d[u]<d[v]? u:v;
  }
  inline void upd(ll u, T &val){
    ll idx1=id[u], idx2=id1[u];
    st1.modify(idx1, val);
    st2.modify(idx2, val);
  }
  inline ll que(ll u, ll v){
    ll l, r, node=lca(u,v);
    T ans1, ans2, cur; 
    ans1.clear(); ans2.clear();
    while(u!=-1){
      if(rt[u]==rt[node]){
        r=id1[node], l=id1[u];
        cur=st2.que(l,r);
        ans1=st2.Op(ans1, cur);
        u=-1;
      }
      else{
        l=id1[u], r=id1[rt[u]];
        cur=st2.que(l,r+1);
        ans1=st2.Op(ans1, cur);
        u=p[rt[u]];
      }
    }
    while(v!=-1){
      if(rt[v]==rt[node]){
        r=id[v], l=id[node];
        cur=st1.que(l+1,r+1);
        ans2=st1.Op(cur, ans2);
        v=-1;
      }
      else{
        l=id[rt[v]], r=id[v];
        cur=st1.que(l,r+1);
        ans2=st1.Op(cur, ans2);
        v=p[rt[v]];
      }
    }
    return st1.Op(ans1,ans2).val;
  }
  inline void build(){
    gid=0, st1.n=n, st2.n=n;
    make();
    go(0,0);
    goes();
    FER(i,0,n) {
      T cur; 
      cur.ta=1, cur.l=1;
      cur.r=1, cur.val=f[1];
      st1.t[i+n]=cur, st2.t[i+n]=cur;
    }
    st1.build(), st2.build();
  }
};