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
#define TAM 100010
  
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
int Lis[TAM];
int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60,80 };
int LIS(int n){
  int max_lis=-1;
  f(i,0,n) Lis[i]=1;
  f(i,1,n){
    f(j,0,i){
      if(arr[i]>arr[j] && Lis[i]<Lis[j]+1) Lis[i]=Lis[j]+1;
    }
    if ( max_lis < Lis[i] )
         max_lis = Lis[i];
  }
  return max_lis;
}
int main() {
    int n = sizeof(arr)/sizeof(arr[0]);
    debug(n);
    int lis=LIS(n);
    debug(lis);
    return 0;
}