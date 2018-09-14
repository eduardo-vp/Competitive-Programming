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
#define d 256
  
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
void Rabin_Karp(string source,string pattern, int q){
 int n=source.size();int m=pattern.size();
 int p=0;                       // hash value for pattern
 int t=0;               // hash value for text
 int h=1;                       // d^(m-1) value
 // Calculo el valor de d^(m-1) --> Pre-procesamiento en O(n)
 f(i,0,m-1){
 	h=(d*h)%q;
 }
 // Multiply each character by its place value and obtain the hash value
 // Initial Hash values of current sliding text window and the pattern is being calculated
  f(i,0,m){
   p=(d*p+pattern[i])%q;
   t=(d*t+source[i])%q;
  }
 
  f(i,0,n-m){
 
	// Check if the current sliding window of text and pattern have same hash values
 
	if(t==p){
	// Check if all characters are same or it's a SPURIOUS HIT !
	int index=0; 
	f(j,0,m){
		if(source[i+j]!=pattern[j]) {
		break;
		}
		index++;
    }
    if(index==m) cout<<"Pattern matched at index "<<i<<endl;
	}
	// Now compute the next sliding window for the text using previous value..
	if(i<n-m){
	t = (d*(t - source[i]*h) + source[i+m])%q;
	 
	// We might get negative value of t, converting it to positive
	 
	if(t < 0)
	t = (t + q); 
    }
 }
}
int main() {
     string source;string pattern;int q;
     cin>>source;cin>>pattern;
     scanf("%d",&q);
     debug(source);debug(pattern);
     Rabin_Karp(source,pattern,q);
    return 0;
}