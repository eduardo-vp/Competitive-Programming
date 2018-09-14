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
vector < vi > adj;
int main() {
     int n,l,a,b;
     while(scanf("%d",&n)){
     	if(n==0) break;
     	scanf("%d",&l);
     	f(i,0,n){
     		adj.push_back(vi());
     	}
     	f(i,0,l){
     		scanf("%d %d",&a,&b);
     		adj[a].push_back(b);
     	}
     	//proceso para verificar si es bipartito
     	queue<int> q;q.push(0);
     	int color[n+1];
     	clr(color,-1);
     	color[0]=0;
     	bool isBipartite=true;
     	while(!q.empty() && isBipartite){
     		int u=q.front();
     		q.pop();
     		f(j,0,(int)adj[u].size()){
     			int v=adj[u][j];
     			if(color[v]==-1){
     				color[v]=1-color[u];//cambio de color
     				q.push(v);
     			}
     			else if(color[v]==color[u]){
     				isBipartite=false;
     				break;
     			}
     		}
     	}
     	if(!isBipartite){
     		printf("NOT BICOLORABLE.\n");
     	}else printf("BICOLORABLE.\n");
     	adj.clear();
     }
    return 0;
}