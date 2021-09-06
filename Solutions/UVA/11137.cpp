#include <bits/stdc++.h>
#define trace(x) cout << #x << " = " << x << endl
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define MOD 1000000
using namespace std;
typedef vector<int> vi;
typedef long long ll;

ll ways[10100];
int coins[25];

void init(){
  for(int i = 1; i <= 21; i++ ){
    int power = 1;
    for(int j = 0; j < 3; j++) power *= i;
    coins[i] = power;
  }
  ways[0] = 1LL;
  for(int i = 1; i <= 21; i++){
    int value = coins[i];
    for(int j = 1; j <= 10000; j++){
      if(j - value >= 0 ) ways[j] += ways[j-value];
    }
  }
}

int main(){

  int n;
  init();
  while(cin >> n)
    cout << ways[n] << endl;
  return 0;
}