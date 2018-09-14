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
int main() {
    int L, n, x, r;
    int i, j, k;
    pair<int, int> range[10000];
    while(scanf("%d %d", &L, &n) == 2 && L) {
         f(i,0,n) {
            scanf("%d %d", &x, &r);
            range[i] = mp(x-r, x+r);
        }
        sort(range, range+n);
        //r= rango de inicio, en este caso es de [0,L]
        int tr, r = 0, ret = n;
        i = 0;
        while(r < L) {
            tr = r;
            while(i < n && range[i].first <= r) {
                if(tr < range[i].second)
                    tr = range[i].second;
                i++;
            }
            if(tr == r) break;
            r = tr;
            ret--;
        }
        //para este caso , cada disminucion de ret, vendria a ser como si hayamos
        // tomado un intervalo 
        if(r < L)
            puts("-1");
        else
            printf("%d\n", ret);
    }
    return 0;
}