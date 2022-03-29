
vector< pair< vector<int>,int > > Radixsort(vector< vector<int> > &vec){
  int lmax = 0, m = 0;
  for(vector<int> &v : vec){
    lmax = max(lmax,sz(v));
    for(int &x : v) m = max(m,x+1);
  }
  deque<int> dq;
  vector< queue<int> > q(m);
  vector< vector<int> > hold(lmax);
  for(int i = 0; i < sz(vec); ++i){
    hold[sz(vec[i])-1].pb(i);
  }
  for(int i = lmax-1; i >= 0; --i){
    for(int x : hold[i]) dq.push_front(x);
    while(sz(dq)){
      int x = dq.front();
      dq.pop_front();
      q[vec[x][i]].push(x);
    }
    for(int j = 0; j < m; ++j){
      while(sz(q[j])){
        dq.push_back(q[j].front());
        q[j].pop();
      }
    }
  }
  vector< pair< vector<int>,int > > ans(sz(vec));
  for(int i = 0; i < sz(vec); ++i){
    int x = dq.front(); dq.pop_front();
    ans[i] = mp(vec[x],x);
  }
 
  return ans;
}
 
int vist[N];
int lev1,lev2,id1[N],id2[N],pai1[N],pai2[N];
vector<int> noleaf1[N],noleaf2[N],leaf1[N],leaf2[N],tup1[N],tup2[N];
 
void dfs1(Tree &tree, int u, int p, int dep = 0){
  pai1[u] = p;
  lev1 = max(lev1,dep);
  vist[u] = 1;
  int tam = 0;
  for(int v : tree[u]) if(!vist[v]){
    dfs1(tree,v,u,dep+1);
    tam++;
  }
  if(tam >= 1) noleaf1[dep].pb(u);
  else leaf1[dep].pb(u), id1[u] = 0;
}
 
void dfs2(Tree &tree, int u, int p, int dep = 0){
  pai2[u] = p;
  lev2 = max(lev2,dep);
  vist[u] = 1;
  int tam = 0;
  for(int v : tree[u]) if(!vist[v]){
    dfs2(tree,v,u,dep+1);
    tam++;
  }
  if(tam >= 1) noleaf2[dep].pb(u);
  else leaf2[dep].pb(u), id2[u] = 0;
}
 
bool isomorphic(Tree &t1, int r1, Tree &t2, int r2, int ban){
  for(int i = 0; i < N; ++i){
    vist[i] = 0;
    noleaf1[i].clear(), noleaf2[i].clear(); 
    leaf1[i].clear(), leaf2[i].clear();
    tup1[i].clear(), tup2[i].clear();
  }
  vist[ban] = 1;
  lev1 = lev2 = 0;
  dfs1(t1,r1,r1);
  FER(i,0,N) vist[i] = 0; vist[ban] = 1;
  dfs2(t2,r2,r2);
  if(lev1 != lev2) return false;
  vector<int> l1,l2;
  for(int x : leaf1[lev1]) l1.pb(x);
  for(int x : leaf2[lev2]) l2.pb(x);
  if(sz(l1) != sz(l2)) return false;
  
  for(int i = lev1-1; i >= 0; --i){ 
    vector< vector<int> > v1,v2;
    for(int u : l1){
      tup1[pai1[u]].pb(id1[u]);
    }
    for(int u : l2){
      tup2[pai2[u]].pb(id2[u]);
    }
    for(int u : noleaf1[i])
      v1.pb(tup1[u]);
    for(int u : noleaf2[i])
      v2.pb(tup2[u]);
    if(sz(v1) != sz(v2)) return false;
    
    vector< pair< vector<int>,int > > res1, res2;
    res1 = Radixsort(v1);
    res2 = Radixsort(v2);
    int cnt = 1;
    l1.clear(); l2.clear();
 
    for(int x : leaf1[i]) l1.pb(x);
    for(int x : leaf2[i]) l2.pb(x);
    for(int j = 0; j < sz(res1); ++j){
      if(res1[j].first != res2[j].first) return false;
      if(j > 0 and res1[j].first != res1[j-1].first) cnt++;
      l1.pb(noleaf1[i][res1[j].second]);
      l2.pb(noleaf2[i][res2[j].second]);
      id1[noleaf1[i][res1[j].second]] = cnt;
      id2[noleaf2[i][res2[j].second]] = cnt;
    }
  }
  return true;
}
