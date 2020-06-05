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
int n,m;
vector <vi> adj;
vi ts;
bool vis[100+5];
void dfs(int u){
 vis[u]=true;
 f(i,0,int(adj[u].size())){
 	if(!vis[adj[u][i]]){
 		dfs(adj[u][i]);
 	}
 }
 ts.pb(u);
}
int main() {
     int a,b;
     while(scanf("%d %d",&n,&m)){
     	if(n==0 && m==0) break;
     	f(i,0,n) adj.pb(vi());
     	f(i,0,m){
     		scanf("%d %d",&a,&b);
     		adj[a-1].pb(b-1);
     	}
     	clr(vis,false);
     	f(i,0,n){
     		if(!vis[i]){
     			dfs(i);
     		}
     	}
     	fd(i,ts.size()-1,0){
     		if(i==0) printf("%d\n",ts[i]+1);
     		else printf("%d ",ts[i]+1);
     	}
     	adj.clear();
     	ts.clear();
     }
    return 0;
}