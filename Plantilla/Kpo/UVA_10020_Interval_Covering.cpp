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
int M,cont;
struct interval{
 int L,R;
 bool operator <(const interval &s) const{
 	if(L<s.L){
 		return true;
 	}else if (L==s.L){
 		return (R>s.R);
 	}else return false;
 }
};
interval arr[MAXN];
 //para este problema se asume que empieza desde [0..M]!!!!
bool isNotCut(int a,int b){
	return (b< 0 || a > M);
}
int main() {
     int T,a,b;
     scanf("%d",&T);
     f(l,0,T){
     	if(l>0) printf("\n");
     	cont=0;
     	scanf("%d",&M);
     	while(scanf("%d %d",&a,&b)){
     	  if(a==0 && b==0) break;
     	  if(isNotCut(a,b)) continue;
     	  arr[cont].L=a;arr[cont].R=b;
     	  cont++;
     	}
     	sort(arr,arr+cont);//paso necesario
     	bool failed = false;
     	// LeftEnd save the current left end and
        // rightEnd save the current right end
        int leftEnd = 0, rightEnd;  
          // The next index to put in the result
       int index = 0;
       vector<interval> output;
      
     	//Interval Covering
     	if(cont>0 && arr[0].L<=0){
     		rightEnd=arr[index].R;
     		f(i,1,cont){
     			if(arr[i].L<=leftEnd){
     				// printf("%d->%d\n",arr[i].L,leftEnd);
     				if(arr[i].R>rightEnd){
     					rightEnd=arr[i].R;//selecciono el más extenso
     					index=i;
     				}
     			}else if(arr[i].L>leftEnd && arr[i].R>rightEnd){
     				if(arr[i].L>rightEnd){
     					failed=true;
     					break;
     				}
     				//si esta totalmente cubierto
     				if(arr[index].R>=M) break;
     				//si no, actualizamos el resultado
     				output.pb(arr[index]);
     				leftEnd = rightEnd;
     				rightEnd = arr[i].R;
     				index=i;
     			}
     		}
     		 output.pb(arr[index]);
     	}else{
     		failed=true;
     	}
     	if(!failed && rightEnd>=M){
     		printf("%d\n",SZ(output));
     		f(i,0,SZ(output)){
     			printf("%d %d\n",output[i].L,output[i].R);
     		}
     	}else{
     		printf("0\n");
     	}
     	
        
     }
    return 0;
}