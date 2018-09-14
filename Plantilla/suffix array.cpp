
struct SA{
  ll n,t;
  ll p[N], r[N], h[N];
  string s;
  ll rmq[M][N], flog2[N];
  inline void fix_index(ll b, ll e){
    ll lastpk, pk, d;
    lastpk=p[r[b]+t];
    d=b;
    FER(i,b,e){
      if(((pk=p[r[i]+t]) !=lastpk) && (b>lastpk || pk>=e)){
        lastpk = pk;
        d=i;
      }
      p[r[i]]=d;
    }
  }
  inline void suf_arr(){
    s[n++]='$';
    ll bc[256];
    FER(i,0,256) bc[i]=0;
    FER(i,0,n) bc[(ll)s[i]]++;
    FER(i,1,256) bc[i]+=bc[i-1];
    IFR(i,n-1,0) r[--bc[(ll)s[i]]]=i;
    IFR(i,n-1,0) p[i]=bc[(ll)s[i]];
    for(t=1;t<n;t<<=1){
      for(ll i=0,j=1;i<n;i=j++){
        while(j<n && p[r[j]]==p[r[i]]) ++j;
        if(j-i>1){
          sort(r+i,r+j, [&](const ll &i, const ll &j){return p[i+t]<p[j+t];});
          fix_index(i,j);
        }
      }
    }
  }
  inline void initlcp(){
    ll tam=0,j;
    FER(i,0,n-1){
      j=r[p[i]-1];
      while(s[i+tam]==s[j+tam]) ++tam;
      h[p[i]-1]=tam;
      if(tam>0) --tam;
    }
  }
  inline void makelcp(){
    initlcp();
    FER(i,0,n-1) rmq[0][i]=h[i];
    ll lg=0,pw=1;
    do{
      FER(i,pw,2*pw) flog2[i]=lg;
      lg++;pw*=2;
      FER(i,0,n-1){
        if(i+pw/2 < n-1) rmq[lg][i]=min(rmq[lg-1][i], rmq[lg-1][i+pw/2]);
        else rmq[lg][i]=rmq[lg-1][i];
      }
    } while(pw<n);
  }
  inline ll lcp(ll i, ll j){
    if(i==j) return n-r[i]-1;
    ll lg=flog2[j-i], pw=(1<<lg);
    return min(rmq[lg][i], rmq[lg][j-pw]);
  }
  inline void build(){
    fill(p,0);
    fill(r,0);
    fill(h,0);
    fill(rmq,0);
    fill(flog2,0);
    n=sz(s);
    suf_arr();
    makelcp();
  }
}sa;