// One, two, three, let's go
// 저 바다 건너 들릴 듯 소리 질러
// corner cases // int vs ll // clear structures // statement // doublesz // line order // 0-1-indexed
#include <bits/stdc++.h>
#define endl '\n'
#define REP(i,n) for (int i = 0; i < (int)(n); ++i)
#define trace(x) cerr << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long Long;
typedef pair<int,int> ii;
const int B = 61;

Long basis[B];

void insert(Long x) {
  for (int i = B - 1; i >= 0; --i) {
    if ((x & (1LL << i)) == 0) continue;
    if (!basis[i]) {
      basis[i] = x;
      break;
    }
    x ^= basis[i];
  }
}

int main() {

  fastio;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    Long x;
    cin >> x;
    insert(x);
  }

  Long ans = 0;
  for (int i = B - 1; i >= 0; --i) {
    if (ans & (1LL << i)) continue;
    ans ^= basis[i];
  }

  cout << ans << endl;

  return 0;
}
