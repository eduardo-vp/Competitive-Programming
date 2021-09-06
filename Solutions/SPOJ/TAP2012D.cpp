// dile a la jardinera que traigo flores
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define tm1 ff
#define tm2 ss.ff
#define tm3 ss.ss
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define all(v) (v).begin(),(v).end()
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define IFR(i,a,b) for(int i = int(a); i >= int(b); i--)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 100020
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Trie{
  int cont;
  int ans;
  int used[N];
  int cant[N];
  map<char,int> to[N];
  
  Trie(){ ans = 0; cont = 1; fill(cant,0); fill(used,0); }

  void insert(string &cad){
    int cur = 0;
    for(char c : cad){
      if(!to[cur].count(c))
        to[cur][c] = cont++;
      cur = to[cur][c];
      cant[cur]++;
    }
  }
  
  void process(string &cad){
    int cur = 0;
    for(char c : cad){
      if(!to[cur].count(c)) break;
      cur = to[cur][c];
      if(used[cur] < cant[cur]){
        used[cur]++;
        ans++;
      }
    }
  }

  int solve(){
    return ans;
  }
};

int main(){

  fastio; 
  int n = 0;
  while(cin >> n){
    if(n == -1) break;
    string cad;
    Trie t;
    FER(i,0,n){
      cin >> cad;
      t.insert(cad);
    }
    FER(i,0,n){
      cin >> cad;
      t.process(cad);
    }
    cout << t.solve() << endl;
  }

  return 0;
}