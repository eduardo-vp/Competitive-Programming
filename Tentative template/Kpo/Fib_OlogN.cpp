#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <complex>
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
void multiply(int F[][2],int M[][2]){
  int x =  F[0][0]*M[0][0] + F[0][1]*M[1][0];
  int y =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
  int z =  F[1][0]*M[0][0] + F[1][1]*M[1][0];
  int w =  F[1][0]*M[0][1] + F[1][1]*M[1][1];
 
  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;	
}
void power(int F[][2],int n){
	if(n==0|| n==1) return;
  	int M[2][2] = {{1,1},{1,0}};
  	power(F,n/2);
  	multiply(F,F);
  	if(n%2!=0){
  		multiply(F,M);
  	}
}
int fib(int n){
	int F[2][2]={{1,1},{1,0}};
	if(n==0) return 0;
	power(F,n-1);
	return F[0][0];
}

int main() {
     printf("%d\n",fib(9));
    return 0;
}