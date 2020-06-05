struct ST{
  T1 lazy[4*N]; 
  T tree[4*N]; 
  ll ar[N];
  ll n;
  inline T Op(T &val1, T &val2){
    return ty;
  }
  inline void updatepro(ll laz,ll id, ll l,ll r){
    ll ta=r-l;
    tree[id]+=ta*laz;
    lazy[id]+=laz;
  }
  inline void proh(ll id, ll l,ll r){
    ll mid=(r+l)>>1;
    updatepro(lazy[id],id<<1,l,mid);
    updatepro(lazy[id],id<<1|1,mid,r);
    lazy[id]=val;// neutro
  }
  inline void updateRange(ll x, ll y, T val, ll id, ll l,ll r){
    if(x>=r || y<=l) return;
    if(x<=l && r<=y){
      updatepro(val,id,l,r);
      return;
    } 
    proh(id,l,r);ll mid=(l+r)>>1;
    updateRange(x,y,val,id<<1,l,mid);
    updateRange(x,y,val,id<<1|1,mid,r);
    tree[id]=Op(tree[id<<1],tree[id<<1|1]);
  }
  inline T getSum(ll x,ll y,ll id,ll l,ll r){
    if(x>=r || l>=y) {T ans; ans.clear();return ans;}
    if(x<=l && r<=y) return tree[id];
    proh(id,l,r);ll mid=(l+r)>>1;
    T left, right;
    left=getSum(x,y,id<<1,l,mid);
    right=getSum(x,y,id<<1|1,mid,r);
    return Op(left, right);
  }
  inline void build1( ll id, ll l, ll r){
    if (l > r) return ;
    if (r-l<2){
      //asignar valores
      tree[id]=T;
      return;
    }
    ll mid = (l + r)>>1;
    build1(id<<1, l,mid); build1(id<<1|1, mid, r);
    tree[id] = Op(tree[id<<1 ] , tree[id<<1|1]);
  }
  inline void upd(ll x, ll y, T val){
    updateRange(x,y,val,1,0,n);
  }
  inline void build(){
    fill(lazy,val);//val neutro
    build1(1,0,n);
  }
  inline T que(ll x, ll y){
    return getSum(x,y,1,0,n);
  }
}st;