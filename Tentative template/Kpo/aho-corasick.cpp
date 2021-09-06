#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <numeric>
#include <list>
#define FOR(i,A) for(typeof (A).begin() i = (A).begin() ; i != (A).end() ; i++)
#define mp make_pair
#define debug( x ) cout << #x << " = " << x << endl
#define clr(v,x) memset( v, x , sizeof v )
#define all(x) (x).begin() , (x).end()
#define rall(x) (x).rbegin() , (x).rend()
#define f(i,a,b) for(int i = a ; i < b ; i++)
#define fd(i,a,b) for(int i = a ; i >= b ; i--)
#define PI acos( -1.0 )
#define EPS 1E-9
#define TAM 100010
 
using namespace std;
 
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
 
char T[ 100010 ] ;
int sig[ TAM ][ 260 ] ;
vector<int> final[ TAM ] ;
int fail[ TAM ] ;
bool enc[ 1010 ] ;
int end ;
 
void init(){
    end = 1 ;
}
 
void add( string s , int idx ){
    int len = s.size() ;
    int nodo = 0 ;
    f( i , 0 , len ){
        int c = s[ i ] ;
        if( !sig[ nodo ][ c ] ){
            sig[ nodo ][ c ] = end++ ;
        }
        nodo = sig[ nodo ][ c ] ;
    }
    final[ nodo ].push_back( idx ) ;
}
 
void build(){
    queue<int> q ;
    f( i , 0 , 260 ){
        int next = sig[ 0 ][ i ] ;
        if( next ){
            fail[ next ] = 0 ;
            q.push( next ) ;
        }
    }
    while( !q.empty() ){
        int nodo = q.front() ; q.pop() ;
        f( i , 0 , 260 ){
            int next = sig[ nodo ][ i ] ;
            int rev = sig[ fail[ nodo ] ][ i ] ;
            if( !next ) sig[ nodo ][ i ] = rev ;
            else{
                q.push( next ) ;
                fail[ next ] = rev ;
                f( j , 0 , final[ rev ].size() ) final[ next ].push_back( final[ rev ][ j ] ) ;
            }
        }
    }
}
 
void search(){
    int len = strlen( T ) ;
    int nodo = 0 ;
    f( i , 0 , len ){
        int c = T[ i ] ;
        while( nodo != 0 && !sig[ nodo ][ c ] ) nodo = fail[ nodo ] ;
        nodo = sig[ nodo ][ c ] ;
        f( j , 0 , final[ nodo ].size() ) enc[ final[ nodo ][ j ] ] = true ;
    }
}
 
int main(){
  int k;
  scanf("%d",&k);
  while(k--){
      scanf("%s" , T ) ;
      int q;
      scanf("%d" , &q ) ;
      init() ;
      int j;
      for(j=0;T[j];j++){
        for(char c='A';c<='Z';c++) sig[j][c] = 0;
        for(char c='a';c<='z';c++) sig[j][c] = 0;
        final[j].clear();
      }
      for(char c='A';c<='Z';c++) sig[j][c] = 0;
      for(char c='a';c<='z';c++) sig[j][c] = 0;
      final[j].clear();
      char s[ 1010 ] ;
      f( i , 0 , q ){
          scanf("%s" , s ) ;
          add( s , i ) ;
      }
      
      build() ;
      search() ;
      f( i , 0 , q ) printf("%s\n" , enc[ i ] ? "y" : "n" ) ;
    }
    return 0 ;
}