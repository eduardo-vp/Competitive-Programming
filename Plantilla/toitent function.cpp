ll lp[N], phi[N];
vi pr;
inline void build(ll n){
  phi[1]=1;
  FER(i,2,n+1){
    if(lp[i]==0){
      lp[i]=i;
      phi[i]=i-1;
      pr.pb(i); 
    }
    else{
      if(lp[i]==lp[i/lp[i]]) phi[i]=phi[i/lp[i]]*lp[i];
      else phi[i]=phi[i/lp[i]]*(lp[i]-1);
    }
    for(ll j=0; j<sz(pr) && pr[j]<=lp[i] && i*pr[j]<=n; ++j) lp[i*pr[j]]=pr[j];
  }
}