
struct Range{
  vector<tri> v,v1;
  Range(){}
  Range(vector<tri> &v, vector<tri> &v1): v(v),v1(v1){}
};
struct MO{
  ll q,n,ta;
  Range rn[N1];
  vector<tri> v;
  long long ans[N];
  ll vis[N2],ar[N];
  MO(){}
  inline void order(){
    ll l,r,id;
    n=sqrt(ta);
    sort(all(v));
    FER(i,0,q) rn[(v[i].itm1)/n].v.pb(v[i]);
    fill(vis,0);
    FER(i,0,n+2){
      FER(j,0,rn[i].v.size()){
        l=rn[i].v[j].itm1;
        r=rn[i].v[j].itm2;
        id=rn[i].v[j].itm3;
        rn[i].v1.pb({r,{l,id}});
      }
      sort(all(rn[i].v1));
    }
  }
  inline void Add(ll i, ll &id){
    ans[id]+=(2*vis[ar[i]]+1)*ar[i];
    vis[ar[i]]++;
  }
  inline void Rem(ll i, ll &id){
    ans[id]-=(2*vis[ar[i]]-1)*ar[i];
    vis[ar[i]]--;
  }
  inline void build(){
    ll l,r,id;
    ll curL=0,curR=0;
    long long val=0;
    FER(i,0,n+2){ 
      FER(j,0,rn[i].v1.size()){
        l=rn[i].v1[j].itm2;
        r=rn[i].v1[j].itm1;
        id=rn[i].v1[j].itm3;
        ans[id]=val;
        while(curL<l) Rem(curL++,id);
        while(curL>l) Add(--curL,id);
        while(curR>r) Rem(--curR,id);
        while(curR<r) Add(curR++,id);
        val=ans[id];
      }
    }
  }
}mo;
// asignar ar[] y pushear v a mo
// luego order() y build()