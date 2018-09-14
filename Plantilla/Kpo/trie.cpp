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

int trie[ TAM ][ 30 ] ;
int words[ TAM ] ;
bool final[ TAM ] ;
int cont ;
int n , q ;

void init(){
	cont = 1 ;
	clr( trie , -1 ) ;
	clr( final , 0 ) ;
	clr( words , 0 ) ;
}

void add( string s ){
	int nodo = 0 ;
	f( i , 0 , s.size() ){
		int c = s[ i ] - 'a' ;
		if( trie[ nodo ][ c ] < 0 ) trie[ nodo ][ c ] = cont++ ;
		words[ nodo ]++ ;
		nodo = trie[ nodo ][ c ] ;
	}
	final[ nodo ] = true ;
}

int countWords( string s ){
	int nodo = 0 ;
	f( i , 0 , s.size() ){
		int c = s[ i ] - 'a' ;
		if( trie[ nodo ][ c ] < 0 ) return 0 ;
		nodo = trie[ nodo ][ c ] ;
	}
	return words[ nodo ] ;
}

bool exists( string s ){
	int nodo = 0 ;
	f( i , 0 , s.size() ){
		int c = s[ i ] - 'a' ;
		if( trie[ nodo ][ c ] < 0 ) return false ;
		nodo = trie[ nodo ][ c ] ;
	}
	return final[ nodo ] ;
}

int main(){

	int type ;
	char s[ TAM ] ;
	while( scanf("%d%d" , &n , &q ) == 2 ){
		init() ;
		f( i , 0 , n ) scanf("%s" , s ) , add( s ) ;
		f( i , 0 , q ){
			scanf("%d%s" , &type , s ) ;
			if( type ) printf("%d\n" , countWords( s ) ) ;
			else printf("%s\n" , exists( s ) ? "YES" : "NO" ) ;
		}
	}
	return 0 ;
}

