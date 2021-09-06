// O(k log n), k number of vertices in virtual tree, n number of vertices in tree
// requires __lca(int,int) and arrays st[] and en[] which are the start and end dfs time of each node

vector<int> vt[N]; //Virtual Tree

bool above(int u, int v){
  return st[u] <= st[v] && en[u] >= en[v];
}

bool cmp(int u, int v){ return st[u] < st[v]; }

int buildTree(vector<int> &vert){ //Returns root of vtree
  sort(vert.begin(), vert.end(), cmp);
  int size = sz(vert);
  for(int i = 0; i < size - 1; ++i){
    vert.pb(__lca(vert[i], vert[i + 1]));
  }
  sort(vert.begin(), vert.end(), cmp);
  vert.erase(unique(vert.begin(), vert.end()), vert.end());
  for(int x: vert) vt[x].clear();
  vector<int> stk;
  stk.pb(vert[0]);
  for(int i = 1; i < sz(vert); ++i){
    while(sz(stk) >= 2 && !above(stk.back(), vert[i])){
      vt[stk[sz(stk) - 2]].pb(stk.back());
      stk.pop_back();
    }
    stk.pb(vert[i]);
  }
  while(sz(stk) >= 2){
    vt[stk[sz(stk) - 2]].pb(stk.back());
    stk.pop_back();
  }
  return stk.back();
}
