//Halla maximos de la forma ax+b
//Para hallar minimos, hacer add(-x,-y) y luego el valor retornado multiplicarlo por -1
bool Q;
struct line{
  mutable ll k, m, p;
  bool operator<(const line &o) const{
    return Q? p<o.p: k<o.k;
  }
};
struct LineContainer:multiset<line>{
  const ll inf=LLONG_MAX;
  inline ll div(ll a, ll b){
    return a/b-((a^b)<0 && a%b);
  }
  inline bool isect(iterator x, iterator y){
    if(y==end()){x->p=inf ; return false;}
    if(x->k==y->k) x->p = x->m > y->m? inf:-inf;
    else x->p=div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  inline void add(ll k, ll m){
    auto z=insert({k,m,0}), y=z++, x=y;
    while (isect(y,z)) z=erase(z);
    if(y!=begin() && isect(--x,y)) isect(x,erase(y));
    while((y=x)!=begin() &&(--x)->p >= y->p) isect(x,erase(y));
  }
  inline ll query(ll x){
    assert(!empty());
    Q=1; auto l=*lower_bound({0,0,x}); Q=0;
    return l.k*x+l.m;
  }
};
