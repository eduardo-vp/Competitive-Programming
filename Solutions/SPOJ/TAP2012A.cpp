// dile a la jardinera que traigo flores
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define all(v) (v).begin(),(v).end()
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define IFR(i,a,b) for(int i = int(a); i >= int(b); --i)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int main(){

  fastio; 
  int n;
  while(cin>>n){
    if(n==-1)break;
    vector<int>v(n);
    FER(i,0,n)cin>>v[i];
    while(true){
      int i;
      //FER(i,0,n)cout<<"    "<<v[i];
      //cout<<endl;
      for(i=0;i<n;i++){
        if(v[i]==i+1){
          v[i]=0;
          FER(j,0,i)v[j]++;
          break;
        }
      }
      if(i==n)break;
    }
    bool ans=true;
    FER(i,0,n)if(v[i]!=0)ans=false;
    if(ans)cout<<"S"<<endl;
    else cout<<"N"<<endl;
  
  }
  return 0;
}