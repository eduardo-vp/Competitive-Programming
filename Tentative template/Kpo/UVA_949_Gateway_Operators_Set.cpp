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
#define MAXN 110  
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
typedef vector<pii> vpi;
const int INF = 10000000;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
bool grid[MAXN][MAXN][4];
int vis[MAXN][MAXN];

struct st{
  int x, y,c;
  st( int x=0,int y = 0, int c=0): x(x), y(y), c(c) {}
  const bool operator < ( const st & in ) const {
    if( x == in.x && y == in.y) return c < in.c;
    if( x == in.x) return y < in.y;
    return x < in.x;
  }
};

int main(){
  int n,m;
  while(scanf("%d%d", &m, &n) > 0){
    f(i,0,MAXN) f(j,0,MAXN){
      vis[i][j] = 0;
      f(k,0,4) grid[i][j][k] = false;
    }
    int r; cin >> r;
    f(i,0,r){
      int a,b,c,d;
      scanf("%d%d%d%d", &a,&b,&c,&d);
      f(j,0,4){
        if( a + dx[j] == c && b + dy[j] == d){
          grid[b][a][j] = true;
        }
      }
    }
    int s; cin >> s;
    set<st> moni;
    f(i,0,s){
      int a,b,c;
      scanf("%d%d%d", &a,&b,&c);
      moni.insert( st( b,c,a ));
    }

    queue<st> q;
    q.push(st( 0,0, 0));
    vis[0][0] = 1;
    int resp = 0;
    while( !q.empty()){
      int x= q.front().x, y = q.front().y, c = q.front().c; q.pop();
      if( y == n-1 && x == m-1) {
        resp = c; break;
      }
      f(i,0,4){
        int nx = x + dx[i]; 
        int ny = y + dy[i];
        if( nx < 0 || nx >= m || ny < 0 || ny >= n || vis[ny][nx] || grid[y][x][i] ) continue;
        if( moni.count( st( nx, ny, c+1) ) > 0 ) {
          q.push( st( x, y , c+1));
        } else {
          vis[ny][nx] = 1;
          q.push(st( nx, ny, c+1));
        }
      }
    }
    cout << resp << endl;
  }
  return 0;
}