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
#define MAXN 1024010
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
struct node{
   int value,len;
   char tipo;
};
node st[MAXN*5];
vi a;
void st_build(int vertex, int L, int R) {
  if (L == R) {                             // as L == R, either one is fine
    st[vertex].value =a[L];                                      // store the index
    st[vertex].len=1;
    st[vertex].tipo=-1;
  }
  else {   // recursively compute the values in the left and right substs
    int nL = 2 * vertex, nR = 2 * vertex + 1;
    st_build(nL, L , (L + R) / 2);
    st_build(nR, (L + R) / 2 + 1, R );
    st[vertex].value = st[vertex*2].value + st[vertex*2+1].value; //Calculate its value
    st[vertex].tipo = -1;
    st[vertex].len = R-L+1;
 } 
}
void set_utype(int vertex,char tipo){
	if (tipo=='I') {
        switch(st[vertex].tipo)
        {
            case 'F': st[vertex].tipo = 'E'; break;
            case 'E': st[vertex].tipo = 'F'; break;
            case 'I': st[vertex].tipo = -1; break;
            case -1: st[vertex].tipo = 'I'; break;
            default: break;
        }
    }
    else st[vertex].tipo = tipo;
	
}
void change(int vertex){
	switch(st[vertex].tipo){
		case 'F': st[vertex].value = st[vertex].len; break;
        case 'E': st[vertex].value = 0; break;
        case 'I': st[vertex].value = st[vertex].len-st[vertex].value; break;
        default: return;
	}
	 set_utype(vertex*2,st[vertex].tipo);   //After applying, push down the cast type to its childrend
     set_utype(vertex*2+1,st[vertex].tipo);
     st[vertex].tipo = -1;             //Its cast type is now NULL
}
void update(int vertex,int L,int R,int i,int j,char tipo){
	int mid=(L+R)/2;
	 if (L>=i && R<=j) set_utype(vertex,tipo);   //If it fits in the interval, set it cast type
     change(vertex);                             //Do the cast type
     if (L>=i && R<=j) return;
     else if (L>j || R<i) return;                     //If it's out then quit
     else{
     	update(vertex*2,L,mid,i,j,tipo);
     	update(vertex*2+1,mid+1,R,i,j,tipo);
     	st[vertex].value = st[vertex*2].value+st[vertex*2+1].value;
     }
}
int answer(int vertex, int l, int r, int i, int j) {
     int mid = (l+r)/2;
     change(vertex);   //cambio el vertice
     if (l>=i && r<=j) return(st[vertex].value);//si esta dentro del rango, elijo el valor
     if (l>j || r<i) return(0);//si se sale del rango, gg
     int p1 = answer(vertex*2,l,mid,i,j);
     int p2 = answer(vertex*2+1,mid+1,r,i,j);
     st[vertex].value = st[vertex*2].value+st[vertex*2+1].value;
     return(p1+p2);
}
int main() {
     int t,n,m,q,u,v;
     char ch;
     string s1,s2;
     scanf("%d",&t);
     f(l,1,t+1){
     	a.clear();
     	scanf("%d",&n);
     	f(i,0,n){
     		scanf("%d\n",&m);
     		getline(cin,s1);
     		// debug(s1);
     		f(j,0,m){
     			f(k,0,SZ(s1)){
     			a.pb(int(s1[k])-48);
     			}
     		}
     	}
        st_build(1,0,SZ(a)-1);
     	scanf("%d\n",&q);
     	printf("Case %d:\n",l);
     	int cnt=0;
     	f(i,0,q){
     		 cin >> ch >> u >> v;
     		 //debug(ch);debug(u);debug(v);
     		if (ch!='S') update(1,0,SZ(a)-1,u,v,ch);
            else{
                cnt++;
                cout << "Q" << cnt << ": " << answer(1,0,SZ(a)-1,u,v) << endl;
            }

     	}
     }
    return 0;
}