// oh, the less I know the better
// corner cases // int vs ll // clear structures // statement // doublesz // line order // 0-1-indexed
#include <bits/stdc++.h>
#define endl '\n'
#define fst first
#define snd second
#define pb push_back
#define sz(x) int(x.size())
#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define trace(x) cerr << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int edit_distance(string &a, string &b){
  int n = sz(a), m = sz(b);
  vector< vector<int> > dp(n+1, vector<int>(m+1, 0));
  for(int i = 1; i <= n; ++i){
    dp[i][0] = i;
  }
  for(int i = 1; i <= m; ++i){
    dp[0][i] = i;
  }
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= m; ++j){
      dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
      int cost = a[i-1] != b[j-1];
      dp[i][j] = min(dp[i][j], dp[i-1][j-1] + cost);
    }
  }
  return dp[n][m];
}

int brute_force(string &a, string &b){
  int m = sz(b), ans = 1e9;
  for(int len = 0; len <= m; ++len){
    for(int i = 0; i + len <= m; ++i){
      string s = b.substr(i,len);
      ans = min(ans, edit_distance(a,s));
    }
  }
  return ans;
}

string solve(string &a, string &b){
  int n = sz(a), m = sz(b);
  vector< vector<int> > dp(n+1, vector<int>(m+1, 0));
  vector< vector<ii> > prev(n+1, vector<ii>(m+1, ii(-1,-1)));
  for(int i = 1; i <= n; ++i){
    dp[i][0] = i;
  }
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= m; ++j){
      dp[i][j] = dp[i-1][j] + 1;
      prev[i][j] = ii(i-1, j);
      if(dp[i][j-1] + 1 < dp[i][j]){
        prev[i][j] = ii(i, j-1);
        dp[i][j] = dp[i][j-1] + 1;
      }
      int cost = a[i-1] != b[j-1];
      if(dp[i-1][j-1] + cost < dp[i][j]){
        prev[i][j] = ii(i-1, j-1);
        dp[i][j] = dp[i-1][j-1] + cost;
      }
    }
  }

  /*
  for(int i = 0; i <= n; ++i){
    for(int j = 0; j <= m; ++j){
      cerr << dp[i][j] << " ";
    }
    cerr << endl;
  }
  */

  int lastp = 0;
  for(int i = 1; i <= m; ++i){
    if(dp[n][i] <= dp[n][lastp]){
      lastp = i;
    }
  }

  int x = n, y = lastp;
  while(x > 0 && y > 0){
    ii b = prev[x][y];
    x = b.fst, y = b.snd;
    //assert(x >= 0 && y >= 0);
  }
  string ans;
  for(int i = y; i < lastp; ++i){
    ans += b[i];
  }
  return ans;
}

bool check(string a, string b){
  int ans = brute_force(a,b);
  string best_s = solve(a,b);
  return edit_distance(a,best_s) == ans;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randint(int a, int b){
  return uniform_int_distribution<int>(a,b)(rng);
}

char to_char(int x){
  return 'a' + x;
}

int gen_char(){
  int x = randint(0, 25);
  return to_char(x);
}


string gen_string(){
  int len = randint(0,15);
  string ans;
  REP(i,len) ans += gen_char();
  return ans;
}

int main(){

  fastio;
  string a,b;
  for(int tt = 1; ; ++tt){
    a = gen_string();
    b = gen_string();
    cerr << "test = " << tt << " a = " << a << " b = " << b << endl;
    assert(check(a,b));
  }

  return 0;
}
