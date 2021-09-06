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
#define INF 2000000000
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
typedef vector<pii> vpi;

int t,n,m,S,a,b,w,T;
vector<vii> adj;
int main() {
   int caseNo=1;
     scanf("%d",&t);
     while(t--){
      scanf("%d %d %d %d",&n,&m,&S,&T);
      adj.assign(n,vii());
      f(i,0,m){
        scanf("%d %d %d",&a,&b,&w);
        adj[a].pb(mp(b,w));
        adj[b].pb(mp(a,w));
      }
      vi dist(n,INF);
      dist[S]=0;
      int weight_u_v;
      queue<int> q; q.push(S);
      vi en_cola (n,0); en_cola[S]=1;
      while(!q.empty()){
        int u=q.front();q.pop();en_cola[u]=0;
        f(j,0,SZ(adj[u])){
          int v=adj[u][j].fr;weight_u_v=adj[u][j].sc;
          if(dist[u]+weight_u_v<dist[v]){
            dist[v]=dist[u]+weight_u_v;
            if(!en_cola[v]){
              q.push(v);en_cola[v]=1;
            }
          }
        }
      }
      printf("Case #%d: ", caseNo++);
      if (dist[T] != INF) printf("%d\n", dist[T]);
      else                printf("unreachable\n");
     }
    return 0;
}