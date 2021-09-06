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
#define TAM 10010
 
using namespace std;
 
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
 
char T[ 1010 ] ;
int sig[ TAM ][ 260 ] ;
vector<int> final[ TAM ] ;
int fail[ TAM ] ;
bool enc[ 1010 ] ;
char board[1010][1010];
char pattern[110][110];
int rpta[1010][1010];
int val[110];

int end ;
set<pair<string,int> > s;

int b[510];
void KMPBuild(int m){
  int i=0,j=-1;
  b[0] = -1;
  while(i<m){
    while(j>=0 && val[j] != val[i]) j = b[j];
    i++;j++;
    b[i] = j;
  }
}
int ocur;
void KMP(int k,int patleng,int m){
  int i =0,j=0;
  while(i<m){
    while(j>=0 && rpta[i][k] != val[j]) j=b[j];
    i++; j++;
    if(j==patleng){
      //ocurrencia
      ocur++;
      j = b[j];
    }
  }
}

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
 
void search(int row){
    int len = strlen( T ) ;
    int nodo = 0 ;
    f( i , 0 , len ){
        int c = T[ i ] ;
        while( nodo != 0 && !sig[ nodo ][ c ] ) nodo = fail[ nodo ] ;
        nodo = sig[ nodo ][ c ] ;
        f( j , 0 , final[ nodo ].size() ){
          rpta[row][i] = final[nodo][j];
          enc[ final[ nodo ][ j ] ] = true ;
        }
    }
}
 
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    int h,w,r,c;
    scanf("%d %d",&r,&c);
    for(int i=0;i<r;i++) scanf("%s",board[i]);
    scanf("%d %d",&h,&w);
    int b=1;
    while(b--){
      s.clear();
      for(int i=0;i<r;i++)
        for(int j=0;j<c;j++) rpta[i][j] = 0;
        for(int i=0;i<h;i++) scanf("%s",pattern[i]);
        
        //Los strings iguales se obvian
        for(int i=0;i<h;i++) s.insert(pair<string,int>(pattern[i],i));
        int aux = 1;
        set<pair<string,int> >::iterator it = s.begin();
        
        int j;
      for(j=0;j<10000;j++){
        for(int i=0;i<260;i++) sig[j][i] = 0;
        final[j].clear();
        fail[j]=0;
      }
      for(int i=0;i<260;i++) sig[j][i] = 0;
      fail[j]=0;
      final[j].clear();
      
        init();
        while(it!=s.end()){
          string auxx = it->first;
          add(auxx,aux);
          val[it->second] = aux;
          it++;
          while(it!=s.end() && it->first==auxx){
            val[it->second] = aux;
            it++;
          }
          aux++;
        }
        build() ;
        KMPBuild(h);
        
        
        for(int k=0;k<r;k++){
          strcpy(T,board[k]);
          search(k) ;
        }
        ocur=0;
        for(int k=0;k<c;k++){
          KMP(k,h,r);
        }
        cout<<ocur<<endl;
      }
  }
    return 0 ;
}