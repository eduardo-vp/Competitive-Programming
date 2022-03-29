/* Solves dynamic connectivity offline in O((n+m) sqrt(m log n)) */
/* queries : add, rem, connected? */

typedef long long ll;
typedef pair<int,int> ii;
const int MOD = 1e9+7;
const int SQ = 320;
const int N = 4e5+20;

struct DSUrb {
  int p[N], rk[N], val[N], cnt;
  int* where[N];
  DSUrb(){ cnt = 0; }
  void reset(int n){
    REP(i,0,n+1) p[i] = i, rk[i] = 1;
    cnt = 0;
  }
  void rollback(){
    while(cnt > 0){
      *where[cnt-1] = val[cnt-1];
      --cnt;
    }
  }
  int getp(int a){
    return (a == p[a] ? a : getp(p[a]));
  }
  void unite(int a, int b){
    a = getp(a), b = getp(b);
    if(a == b) return;
    if(rk[a] < rk[b]) swap(a,b);
    where[cnt] = &rk[a];
    val[cnt++] = rk[a];
    where[cnt] = &p[b];
    val[cnt++] = p[b];
    assert(cnt < N);
    rk[a] += rk[b];
    p[b] = a;
  }
  int getpFast(int a){
    return (a == p[a] ? a : (p[a] = getpFast(p[a])));
  }
  void uniteFast(int a, int b){
    a = getpFast(a), b = getpFast(b);
    if(a == b) return;
    if(rk[a] < rk[b]) swap(a,b);
    rk[a] += rk[b];
    p[b] = a;
  }
};

DSUrb Uf;

map<ii,int> mp;

ii make_edge(int a, int b){
  if(a > b) swap(a,b);
  return ii(a,b);
}

int get_edge(ii edge){
  if(!mp.count(edge)){
    int x = sz(mp);
    mp[edge] = x;
  }
  return mp[edge];
}

int n,m;
ii edge[N];
vector<ii> vec;
int type[N],x[N],y[N],active[N],used[N],edge_id[N];

void rebuild(int l){
  int r = min(l+SQ,m);
  Uf.reset(n+1);
  REP(i,0,n+1) active[i] = used[i] = 0;
  for(int i = 0; i < l; ++i) if(type[i] == 1){
    int id = edge_id[i];
    used[id] = 1;
    active[id] ^= 1;
  }
  for(int i = l; i < r; ++i) if(type[i] == 1){
    int id = edge_id[i];
    used[id] = 0;
  }
  vec.clear();
  for(int i = 0; i < l; ++i) if(type[i] == 1){
    int id = edge_id[i];
    if(used[id] && active[id]){
      active[id] = false;
      Uf.uniteFast(edge[i].fst,edge[i].snd);
    }else if(!used[id] && active[id]){
      active[id] = false;
      vec.pb(edge[i]);
    }
  }
}

char op[100];

int main(){

  scanf("%d %d",&n,&m);
  for(int i = 0; i < m; ++i){
    // op can be {add,rem,connected}
    scanf(" %s %d %d",op,x+i,y+i);
    if(op[0] == 'a' || op[0] == 'r') type[i] = 1;
    else type[i] = 2;
    x[i]--; y[i]--;
    if(x[i] > y[i]) swap(x[i],y[i]);
    edge[i] = {x[i],y[i]};
    edge_id[i] = get_edge(edge[i]);
  }

  for(int i = 0; i < m; ++i){
    if(i % SQ == 0) rebuild(i);
    if(type[i] == 1){
      Uf.rollback();
      ii e = edge[i];
      auto it = find(vec.begin(),vec.end(),e);
      if(it == vec.end()) vec.pb(e);
      else vec.erase(it);
    }else{
      for(ii e : vec){
        Uf.unite(e.fst,e.snd);
      }
      ii e = edge[i];
      int r = Uf.getp(e.fst) == Uf.getp(e.snd);
      if(r) puts("YES");
      else puts("NO");
    }
  }

  return 0;
}
