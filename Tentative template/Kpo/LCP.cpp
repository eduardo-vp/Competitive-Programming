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
char T[TAM];
int n;
int RA[TAM],tempRA[TAM];
int SA[TAM],tempSA[TAM];
int LCP[TAM],PLCP[TAM],Phi[TAM];
int c[TAM];
void countingSort(int k){
	int i,sum,maxi=max(300,n);//hasta 255 caracteres o lontigud de n
	clr(c,0);//inicializo tabla
	for(i=0;i<n;i++){//cuenta la frecuencia para cada ranking entero
		c[i+k<n ? RA[i+k] : 0]++;
	}
	for(i =sum =0;i<maxi;i++){
		int t=c[i];c[i]=sum;sum+=t;
	}
	for(i=0;i<n;i++){//mezclo el SA sifuera necesario
		tempSA[c[SA[i]+k<n ? RA[SA[i]+k] :0]++]=SA[i];
	}
	for(i=0;i<n;i++){
		SA[i]=tempSA[i];
	}
}
void constructSA(){//limite , 100000 caracteres
	int k,r;
;
    f(i,0,n){
    	RA[i]=T[i];//rankings iniciales
        
    }
    f(i,0,n){
    	SA[i]=i;//inicializo SA:{0,1,2,..,n-1}
    }
    
    for(k=1;k<n;k<<=1){//repito el proceso log n veces
     countingSort(k);//radix sort basado en el segundo item
     countingSort(0);//radix sort basado en el primer item
     tempRA[SA[0]]=r=0;
     f(i,1,n){
     	tempRA[SA[i]]=(RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])? r : ++r;
        //verifico si son el mismo par, mismo rank doy r, si no incremento r	
     }
     f(i,0,n){
     	RA[i]=tempRA[i];
     }
     if(RA[SA[n-1]] == n-1) break;
    }
}
void computeLCP(){
	int L;
	clr(Phi,0);clr(PLCP,0);clr(LCP,0);
	Phi[SA[0]]=-1;//valor por default
	f(i,1,n){//O(n)
		Phi[SA[i]]=SA[i-1];//recuerdo que sufijo estuvo detras del sufijo actual
	}
	for(int i=L=0;i<n;i++){
		if(Phi[i]==-1){
			PLCP[i]=0;continue;//caso especial
		}
		while(T[i+L]==T[Phi[i]+L]) L++;//sabemos por teorema que L se incrementa
		                               //a lo mucho n veces
		PLCP[i]=L;
		L=max(L-1,0);//L se decrementa n veces como maximo
	}
    f(i,0,n){
    	LCP[i]=PLCP[SA[i]];//pongo el permutado LCP en su posicion original
    }
}
int main() {
    n=(int)strlen(gets(T));
    T[n++]='$';
    constructSA();
    int aux=n-2;
    computeLCP();
    printf("%d\n",LCP[aux]);
    f(i,0,n){
    	printf("%2d\t%s\n",SA[i],T+SA[i]);
    }
    return 0;
}