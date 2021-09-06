#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
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
#define rall(x) (x).rbegin() , (x).rend()
#define PI acos( -1.0 )
#define EPS 1E-9
#define TAM 10010
  
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
vi a;
int* LIS(int n){
  
  int* lis = new int[n];
    int b[n];
    int maxLength = 1, pos;
    lis[0] = 1, b[0] = a[0];
 
    for (size_t i = 1; i < n; i++) {
        pos = lower_bound(b, b + maxLength, a[i]) - b;
        lis[i] = pos + 1;
        if (pos == maxLength)    b[maxLength++] = a[i];
        else    b[pos] = a[i];
    }
    return lis;
}
int main() {
     int t,n;
     while(scanf("%d",&t)!=EOF){
      a.clear();
      f(i,0,t){
        scanf("%d",&n);
        a.push_back(n);
      }
      int* lis=LIS(a.size());
        reverse(a.begin(), a.end());
        int* lds = LIS(a.size());
        reverse(lds, lds + a.size());
      int MAX_LIS = -1;
        for (size_t i = 0; i < a.size(); i++)
            MAX_LIS = max(MAX_LIS, min(lis[i], lds[i]));
        printf("%d\n",2*MAX_LIS-1);
     }
    return 0;
}