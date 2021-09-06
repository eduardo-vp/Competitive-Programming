
// Obrigado $$ fR0z $$

struct Node{
  int fmax, smax, cmax; ll sum;
  Node() : fmax(-INF), smax(-INF-1), cmax(0), sum(0){}
  Node(int x) : fmax(x), smax(-INF), cmax(1), sum(x){}
  void merge(Node &a, Node &b){
    fmax = max(a.fmax, b.fmax);
    smax = max(a.smax, b.smax);
    cmax = 0;
    sum = a.sum + b.sum;
    if(fmax == a.fmax) cmax += a.cmax;
    else smax = max(smax, a.fmax);
    if(fmax == b.fmax) cmax += b.cmax;
    else smax = max(smax, b.fmax);
  }
};

Node Op(Node &a, Node &b){
  Node x;
  x.merge(a,b);
  return x;
}

void traceNode(Node x){
  cout << "fmax = " << x.fmax << " smax = " << x.smax << " cmax = " << x.cmax;
  cout << " sum = " << x.sum << endl;
}

struct STBeats{
  int n;
  vector<Node> st;
  vector<int> lazy;
  vector<bool> isLazy;
  STBeats(int n) : n(n), st(4*n+5), lazy(4*n+5,0), isLazy(4*n+5,0){}
  void init(int k, int s, int e, int *a){
    lazy[k] = isLazy[k] = 0;
    if(s+1 == e){ st[k] = Node(a[s]); return; }
    int m = (s+e) / 2;
    init(2*k,s,m,a); init(2*k+1,m,e,a);
    st[k] = Op(st[2*k],st[2*k+1]);
  }
  void push(int k, int s, int e){
    if(isLazy[k]){
      if(lazy[k] >= st[k].fmax){
        isLazy[k] = false;
        return;
      }
      st[k].sum -= 1LL * (st[k].fmax - lazy[k]) * st[k].cmax;
      st[k].fmax = lazy[k];
      if(s+1 < e){
        lazy[2*k] = lazy[k];
        lazy[2*k+1] = lazy[k];
        isLazy[2*k] = isLazy[2*k+1] = true;
      }
      isLazy[k] = false;
    }
  }
  void upd(int k, int s, int e, int a, int b, int v){
    push(k,s,e);
    if(s >= b || e <= a || v >= st[k].fmax) return;
    if(s >= a && e <= b && v > st[k].smax){
      lazy[k] = v;
      isLazy[k] = true;
      push(k,s,e);
      return;
    }
    int m = (s+e) / 2;
    upd(2*k,s,m,a,b,v); upd(2*k+1,m,e,a,b,v);
    st[k] = Op(st[2*k],st[2*k+1]);
  }
  ll sumQuery(int k, int s, int e, int a, int b){
    if(s >= b || e <= a) return 0;
    push(k,s,e);
    if(s >= a && e <= b) return st[k].sum;
    int m = (s+e) / 2;
    return sumQuery(2*k,s,m,a,b) + sumQuery(2*k+1,m,e,a,b);
  }
  int maxQuery(int k, int s, int e, int a, int b){
    if(s >= b || e <= a) return -INF;
    push(k,s,e);
    if(s >= a && e <= b) return st[k].fmax;
    int m = (s+e) / 2;
    return max( maxQuery(2*k,s,m,a,b), maxQuery(2*k+1,m,e,a,b) );
  }
  void init(int *a){ init(1,0,n,a); }
  void upd(int a, int b, int v){ upd(1,0,n,a,b,v); }
  int maxQuery(int a, int b){ return maxQuery(1,0,n,a,b); }
  ll sumQuery(int a, int b){ return sumQuery(1,0,n,a,b); }
};
