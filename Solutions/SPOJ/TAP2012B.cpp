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
  ll n;
  while(cin>>n){
    if(n==-1)break;
    ll ans=0;
    FER(i,1,n+1){//a
      ll num=n+i*i;
      ll sq=sqrt(num);
      FER(j,i,sq+1){
        if(num%j==0){
          ll a=i;
          ll b=j-i;
          ll c=num/j-i;
          if(b<=a&&c<=a)ans++;
        }
      }
    }
    cout<<ans<<endl;
  }
  

  return 0;
}