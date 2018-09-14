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
//Vector de KMP
//Indica la posición del inicio de cada match del string pattern en source
//pueden haber overlapping aaaaa por ejemplo
vector<int> KMP(string source, string pattern){
    int i,j;
    vector<int> B(pattern.size() + 1, -1);
    //pre-procesamiento
    i=0;j=-1;int m=pattern.size();
    B[i]=j;
    while(i<m){
        while(j>=0 && pattern[i]!=pattern[j]) j=B[j];
        i++;j++;
        B[i]=j;
    }
    /*f(i,0,B.size()){
        debug(B[i]);
    }*/
    //busqueda
    i=0;j=0;vi ocurrencias;
    while(i<source.size()){
        while(j>=0 && source[i]!=pattern[j]) j=B[j];
        i++;j++;
        if(j==m){
            ocurrencias.push_back(i-j);
            j=B[j];
        }
    }
    return ocurrencias;
         
}
int main() {
    string source,pattern;
    cin>>pattern;
    cin>>source;
    vi ocurrencias=KMP(source,pattern);
    f(i,0,ocurrencias.size()){
        cout<<ocurrencias[i]<<endl;
    }
    return 0;
}