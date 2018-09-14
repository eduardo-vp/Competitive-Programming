#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <cctype>
#include <stack>
#include <climits>
#include <bitset>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#define FOR(i,A) for(typeof (A).begin() i = (A).begin() ; i != (A).end() ; i++)
#define f(i,a,b) for(int i = a ; i < b ; i++)
#define fd(i,a,b) for(int i = a ; i >= b ; i--)
#define debug( x ) cout << #x << " = " << x << endl
#define clr(v,x) memset( v, x , sizeof v )
#define all(x) (x).begin() , (x).end()
#define mp make_pair
#define pb push_back
#define SZ(a) int(a.size())
#define sc second
#define fr first
#define rall(x) (x).rbegin() , (x).rend()
#define PI acos( -1.0 )
#define EPS 1E-9
#define MAXM 100010
#define MAXN 100010
#define eq(x, y) abs(x-y) < EPS
#define INF 1e8 + 7
#define LSOne(S) (S & (-S))
using namespace std;
  
typedef pair<int,int> ii ;
typedef pair<double,double> fi ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef pair<int,fi> fii ;
typedef vector <fi> vfi;
typedef pair<double,ii> fpi;
typedef vector <ii> vii;
typedef vector<int> vi;
typedef vector<pii> vpi;


// initialization: n + 1 zeroes, ignoring index 0, just using index [1..n]
void ft_create(vi &ft, int n) { ft.assign(n + 1, 0); }

int ft_rsq(const vi &ft, int b) {                      // returns RSQ(1, b)
  int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
  return sum; }

int ft_rsq(const vi &ft, int a, int b) {               // returns RSQ(a, b)
  return ft_rsq(ft, b) - (a == 1 ? 0 : ft_rsq(ft, a - 1)); }

// adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
void ft_adjust(vi &ft, int k, int v) {           // note: n = ft.size() - 1
  for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }

int main() {
  vi ft;                  // idx   0 1 2 3 4 5 6 7  8 9 10, no index 0!
  ft_create(ft, 10);      // ft = {-,0,0,0,0,0,0,0, 0,0,0}
  ft_adjust(ft, 2, 1);    // ft = {-,0,1,0,1,0,0,0, 1,0,0}, idx 2,4,8 => +1
  ft_adjust(ft, 4, 1);    // ft = {-,0,1,0,2,0,0,0, 2,0,0}, idx 4,8 => +1
  ft_adjust(ft, 5, 2);    // ft = {-,0,1,0,2,2,2,0, 4,0,0}, idx 5,6,8 => +2
  ft_adjust(ft, 6, 3);    // ft = {-,0,1,0,2,2,5,0, 7,0,0}, idx 6,8 => +3
  ft_adjust(ft, 7, 2);    // ft = {-,0,1,0,2,2,5,2, 9,0,0}, idx 7,8 => +2
  ft_adjust(ft, 8, 1);    // ft = {-,0,1,0,2,2,5,2,10,0,0}, idx 8 => +1
  ft_adjust(ft, 9, 1);    // ft = {-,0,1,0,2,2,5,2,10,1,1}, idx 9,10 => +1
  printf("%d\n", ft_rsq(ft, 1, 1));  // 0 => ft[1] = 0
  printf("%d\n", ft_rsq(ft, 1, 2));  // 1 => ft[2] = 1
  printf("%d\n", ft_rsq(ft, 1, 6));  // 7 => ft[6] + ft[4] = 5 + 2 = 7
  printf("%d\n", ft_rsq(ft, 1, 10)); // 11 => ft[10] + ft[8] = 1 + 10 = 11
  printf("%d\n", ft_rsq(ft, 3, 6));  // 6 => rsq(1, 6) - rsq(1, 2) = 7 - 1

  ft_adjust(ft, 5, 2);                                       // update demo
  printf("Index: ");
  f(i,0,SZ(ft))
    printf("%d ", i);
  printf("\n");
  printf("FT   : ");
  f(i,0,SZ(ft))
    printf("%d ", ft[i]);
  printf("\n");
} // return 0;