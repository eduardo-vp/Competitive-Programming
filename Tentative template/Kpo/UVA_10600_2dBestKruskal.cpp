#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
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
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
typedef vector<pii> vpi;
vpi edge;
int v[110];
vi sol;
int n;
int best, secondBest;
void init(){
 f(i,0,n) v[i]=i;
}
int findSet(int i){
  if(i==v[i]) return i;
  else return (v[i]=findSet(v[i]));
}
bool isSameset(int i,int j){
  return(findSet(i)==findSet(j));
}
void unionSet(int i,int j){
  v[findSet(i)]=findSet(j);
}
int kruskals(int skip_index){
  init();
  int best_mst=0;
  f(i,0,SZ(edge)){
    if(i==skip_index) continue;
    pii u=edge[i];
    int a=u.sc.fr;int b=u.sc.sc;
    if(isSameset(a,b)) continue;
    best_mst+=u.fr;
    unionSet(a,b);
    if(skip_index==-1) sol.pb(i);
  }
   f(i,1,n){
    if(!isSameset(i,0)) return INT_MAX;
   }
   return best_mst;
}
int main() {
     int t,m,a,b,w;
     cin>>t;
     f(k,0,t){
      cin>>n>>m;
      edge.clear();sol.clear();
      f(i,0,m){
        cin>>a>>b>>w;
        a--;b--;
        edge.pb(mp(w,mp(a,b)));
      }
      sort(all(edge));
      int best_mst = kruskals(-1);
      int second_best_mst = INT_MAX;
      f(i,0,SZ(sol)){
          second_best_mst = min(kruskals(sol[i]), second_best_mst);
      }
      printf("%d %d\n",best_mst,second_best_mst);
     }
    return 0;
}