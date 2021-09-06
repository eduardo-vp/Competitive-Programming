// dile a la jardinera que traigo flores
#include <bits/stdc++.h>
#include <unistd.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

bool zero;
ll l,r,b,on;
string cad;

ll binpow(ll x, ll p){
  ll ans = 1;
  while(p){
    if(p&1) ans *= x;
    x *= x;
    p >>= 1;
  }
  return ans;
}

ll countAll(int n){
  ll ans = 0;
  for(int i = 0; i < n; ++i){
    if(!i) ans += on;
    else{
      if(zero) ans += (on-1)*binpow(on,i);
      else ans += binpow(on,i+1);
    }
  }
  return ans;
}

string t(ll x){
  string ans = "";
  while(x){
    int dig = x%b;
    x /= b;
    ans += string(1,char(dig+'0'));
  }
  reverse(ans.begin(),ans.end());
  return ans;
}

ll count(int st, int mask, int dig, int n){
  for(int i = 0; i < b; ++i)
    if( (mask&(1<<i)) and (cad[i] == 'N') ) return 0;
  ll ans = 0;
  for(int i = st; i < dig; ++i){
    if(cad[i] == 'N') continue;
    ans += binpow(on,n);
  }
  return ans;
}

int bruteforce(int x){
  int ans = 0;
  for(int i = 0; i <= x; ++i){
    string s = t(i);
    if(s == "") s = "0";
    bool valid = true;
    for(char c : s) if(cad[c-'0'] == 'N') valid = false;
    if(valid) ++ans;
  }
  return ans;
}

ll solve(ll x){
  if(x <= 10)
    return bruteforce(x);
  string s = t(x);
  int mask = 0, n = sz(s);
  ll ans = countAll(n-1);
  for(int i = 0; i < n; ++i){
    if(s[i] != '0'){
      ans += count(i == 0,mask,s[i]-'0',n-1-i);
    }
    mask |= (1<<(s[i]-'0'));
  }
  bool all = true;
  for(int i = 0; i < n; ++i)
    if(cad[s[i]-'0'] == 'N') all = false;
  if(all) ++ans;
  return ans;
}

int main(){
  
  fastio;
  while(cin >> l >> r >> b >> cad){
    if(l == -1 and r == -1 and b == -1) break;
    on = 0;
    for(int i = 0; i < b; ++i)
      on += (cad[i] == 'S');
    zero = (cad[0] == 'S');
    ll ans = solve(r) - solve(l-1);
    cout << ans << endl;
  }

  return 0;
}