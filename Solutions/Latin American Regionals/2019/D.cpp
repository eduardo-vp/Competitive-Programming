// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

struct Frac{
  ll a,b;
  Frac(ll a, ll b): a(a),b(b){
    ll gcd = __gcd(a,b);
    a /= gcd;
    b /= gcd;
  }
  bool operator < (Frac &f){
    return a*f.b < b*f.a;
  }
  bool operator == (Frac &f){
    return a*f.b == b*f.a;
  }
  void show(){
    cout << "a = " << a << " b = " << b << endl;
  }
};

Frac min(Frac a, Frac b){
  if(a < b) return a;
  return b;
}

Frac max(Frac a, Frac b){
  if(a < b) return b;
  return a;
}

struct Star{
  ll x,y,b;
  Star(){}
  void read(){
    cin >> x >> y >> b;
  }
};

Frac getPend(Star a, Star b){
  ll x = a.x - b.x;
  ll y = a.y - b.y;
  // rotate 90
  swap(x,y); x *= -1;
  if(x < 0){
    x *= -1;
    y *= -1;
  }
  assert(x != 0);
  return Frac(y,x);
}

bool check(vector<Star> &stars){
  int n = sz(stars);
  Frac mn(-1e9,1), mx(1e9,1);
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j) if(i != j){
      if(stars[i].b == stars[j].b) continue;
      if(stars[i].y == stars[j].y){
        if(stars[i].x < stars[j].x and stars[i].b < stars[j].b){
          return false;
        }
      }else if(stars[i].y > stars[j].y){
        if(stars[i].b > stars[j].b){
          mx = min(mx,getPend(stars[i],stars[j]));
        }else{
          mn = max(mn,getPend(stars[i],stars[j]));
        }
      }
    }
  }
  return mn < mx or mn == mx;
}

void yes(){ cout << "Y" << endl; exit(0); }
void no(){ cout << "N" << endl; exit(0); }

int main(){

  fastio;
  int n;
  cin >> n;
  vector<Star> stars(n);
  for(int i = 0; i < n; ++i){
    stars[i].read();
  }

  // de arriba para abajo
  bool valid = true;
  for(int i = 0; i < n; ++i){
    for(int j = i+1; j < n; ++j){
      if(stars[i].b == stars[j].b) continue;
      if(stars[i].y == stars[j].y) continue;
      if(stars[i].y > stars[j].y and stars[i].b < stars[j].b) valid = false;
      if(stars[j].y > stars[i].y and stars[j].b < stars[i].b) valid = false;
    }
  }
  if(valid) yes();

  // de abajo para arriba
  valid = true;
  for(int i = 0; i < n; ++i){
    for(int j = i+1; j < n; ++j){
      if(stars[i].b == stars[j].b) continue;
      if(stars[i].y == stars[j].y) continue;
      if(stars[i].y < stars[j].y and stars[i].b < stars[j].b) valid = false;
      if(stars[j].y < stars[i].y and stars[j].b < stars[i].b) valid = false;
    }
  }
  if(valid) yes();

  // derecha para izquierda
  if(check(stars)) yes();

  // reflejarlos
  for(int i = 0; i < n; ++i){
    stars[i].x *= -1;
  }

  // izquierda para derecha
  if(check(stars)) yes();

  no();

  return 0;
}

