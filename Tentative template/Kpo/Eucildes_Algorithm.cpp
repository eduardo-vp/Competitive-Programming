#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
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
#define rall(x) (x).rbegin() , (x).rend()
#define PI acos( -1.0 )
#define EPS 1E-9
#define MAXM 110
#define MAXN 100010  
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
int arr[MAXN];
int gcd(int m, int n){
    int r;
    if((m == 0) || (n == 0))
        return 0;
    else if((m < 0) || (n < 0))
        return -1;
    do{
        r = m % n;
        if(r == 0)
            break;
        m = n;
        n = r;
    } while(true);

    return n;
}
int main() {
   int auxi;
     int t;string cad;
     cin>>t;getchar();
     f(i,0,t){
      stringstream ss;
      getline(cin,cad);
      clr(arr,0);
      int maxi=-1;
      ss<<cad;
      int n=0;
      while(ss>>arr[n]) n++;
      f(i,0,n-1){
        f(j,i+1,n){
         auxi=gcd(arr[i],arr[j]);
         if(maxi<auxi) maxi=auxi;
        }
      }
      printf("%d\n",maxi);
     }
    return 0;
}