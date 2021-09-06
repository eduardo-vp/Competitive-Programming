// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 500100
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> ii;

ll n, l[N],one[N];
ll r,rat[N];
char cad[N];

struct Frac{
  ll a,b;
  Frac(ll _a, ll _b) : a(_a),b(_b){
    ll gcd = __gcd(a,b);
    a /= gcd;
    b /= gcd;
  }
  bool operator < (const Frac &other){
    return a*other.b < b * other.a;
  }
  bool operator == (const Frac &other){
    return a == other.a and b == other.b;
  }
};

Frac dist(Frac x, Frac y){
  ll num = x.a * y.b - x.b * y.a;
  if(num < 0) num = -num;
  ll den = x.b * y.b;
  return Frac(num,den);
}

int main(){

  int TC,aux;
  scanf("%d\n",&TC);
  for(int tc = 1; tc <= TC; ++tc){
    scanf("%lld %d.%lld\n",&n,&aux,&r);
    if(aux == 1) r = 1000000;
    scanf("%s\n",cad+1);
    ll ones = 0,len = 0;
    one[0] = l[0] = rat[0] = 0;
    for(int i = 1; i <= n; ++i){
      len++;
      if(cad[i] == '1') ones++;
      l[i] = len;
      one[i] = ones;
      rat[i] = ones*1000000 - r * len;
    }
    n++;
    vector<int> vec(n);
    iota(vec.begin(),vec.end(),0);
    sort(vec.begin(),vec.end(),[&](const int &a, const int &b){
      return rat[a] < rat[b];
    });
    int ans = 0;
    Frac best = Frac(1e9,1);
    for(int i = 1; i < n; ++i){
      int a = vec[i-1], b = vec[i];
      if(a > b) swap(a,b);
      Frac f = Frac((one[b]-one[a])*1000000LL,l[b]-l[a]);
      if(dist(f,Frac(r,1)) == best){
        ans = min(ans,a+1);
      }else{
        if(dist(f,Frac(r,1)) < best){ 
          best = dist(f,Frac(r,1)), ans = a+1;
        }
      }
    }
    printf("Case #%d: %d\n",tc,ans-1);
  }

  return 0;
}
