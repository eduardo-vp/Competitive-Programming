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
#define INF 1000000000
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
typedef vector<pii> vpi;
int main() {
  int V, E, s, u, v, w;
  vector<vii> AdjList;

  /*
  // Graph in Figure 4.17, has negative weight, but no negative cycle
  5 5 0
  0 1 1
  0 2 10
  1 3 2
  2 3 -10
  3 4 3
  // Graph in Figure 4.18, negative cycle exists
  3 3 0
  0 1 1000
  1 2 15
  2 1 -42
  */

  scanf("%d %d %d", &V, &E, &s);

  AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList
  f(i,0,E) {
    scanf("%d %d %d", &u, &v, &w);
    AdjList[u].pb(ii(v, w));
  }

  // Bellman Ford routine
  vi dist(V, INF); dist[s] = 0;
  f(i,0,V-1)  // relax all E edges V-1 times, overall O(VE)
   f(u,0,V)                      // these two loops = O(E)
      f(j,0,SZ(AdjList[u])){
        ii v = AdjList[u][j];        // we can record SP spanning here if needed
        dist[v.first] = min(dist[v.first], dist[u] + v.second);         // relax
      }

  bool hasNegativeCycle = false;
  f(u,0,V)                       // one more pass to check
    f(j,0,SZ(AdjList[u])) {
      ii v = AdjList[u][j];
      if (dist[v.first] > dist[u] + v.second)                 // should be false
        hasNegativeCycle = true;     // but if true, then negative cycle exists!
    }
  printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

  if (!hasNegativeCycle)
    f(i,0,V)
      printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

  return 0;
}