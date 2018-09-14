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
#define MAXN 1005  
using namespace std;
  
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
typedef vector <ii> vii;
typedef vector<int> vi;
typedef vector<pii> vpi;
struct state {
    int x;
    int y;
    int c;
 
    state (int p, int q, int r) {
        x = p;
        y = q;
        c = r;
    }
    state () { }
} a;
 
int row, col;
char matrix [MAXN] [MAXN];
int cost_joe [MAXN] [MAXN];
int cost_fire [MAXN] [MAXN];
int dr [] = {-1, 0, 1, 0};
int dc [] = {0, 1, 0, -1};

//bfs_for_joe es el bfs para joe y a ver hacia donde llega
void bfs_for_joe (int r, int c){
    queue <state> q;
    cost_joe [r] [c] = 0;
    q.push(state (r, c, 0));
 
    while ( !q.empty() ) {
        a = q.front(); q.pop();
 
        f(i,0,4) {
            int nx = a.x + dr [i];
            int ny = a.y + dc [i];
            if ( nx >= 0 && nx < row && ny >= 0 && ny < col && matrix  [nx] [ny] != '#' && cost_joe [nx] [ny] == INT_MAX ) {
                cost_joe [nx] [ny] = a.c + 1;
                q.push(state (nx, ny, a.c + 1));
            }   
        }
    }
}
 
void bfs_for_fire (){
    queue <state> q;
    //primero voy a buscar todos los posibles lugares de fuego
    f(i,0,row) {
        f(j,0,col) {
            if ( matrix [i] [j] == 'F' ) {
                cost_fire [i] [j] = 0;
                q.push(state (i, j, 0));
            }
        }
    }
 
    while ( !q.empty() ) {
        a = q.front(); q.pop();
 
        f(i,0,4) {
            int nx = a.x + dr [i];
            int ny = a.y + dc [i];
            if ( nx >= 0 && nx < row && ny >= 0 && ny < col && matrix  [nx] [ny] != '#' && cost_fire [nx] [ny] > a.c + 1) {
                cost_fire [nx] [ny] = a.c + 1;
                q.push(state (nx, ny, a.c + 1));
            } 
        }
    }
}
 
void reset ()
{
    f(i,0,MAXN) {
        f(j,0,MAXN)
            cost_joe [i] [j] = cost_fire [i] [j] = INT_MAX;
    }
}
 
 
int main(){
    int testCase;
    scanf ("%d", &testCase);
 
    while ( testCase-- ) {
        scanf ("%d %d", &row, &col);
        f(i,0,row) scanf ("%s", matrix [i]);
        reset ();
        f(i,0,row) {
            f(j,0,col) {
                if ( matrix [i] [j] == 'J' ) {
                    bfs_for_joe (i, j);
                    i = row;
                    j = col;
                    break;
                }
            }
        }
 
        bfs_for_fire();
 
        int minimum_escape_time = INT_MAX;
 
        // 1era y ultima fila
        f(i,0,col) {
            if ( cost_fire [0] [i] > cost_joe [0] [i] ) minimum_escape_time = min (minimum_escape_time, cost_joe [0] [i]);
            if ( cost_fire [row - 1] [i] > cost_joe [row - 1] [i] ) minimum_escape_time = min (minimum_escape_time, cost_joe [row - 1] [i]);
        }
 
        // 1st & last col
        f(i,0,row){
            if ( cost_fire [i] [0] > cost_joe [i] [0] ) minimum_escape_time = min (minimum_escape_time, cost_joe [i] [0]);
            if ( cost_fire [i] [col - 1] > cost_joe [i] [col - 1] ) minimum_escape_time = min (minimum_escape_time, cost_joe [i] [col - 1]);
        }
 
        if ( minimum_escape_time == INT_MAX ) printf ("IMPOSSIBLE\n");
        else printf ("%d\n", minimum_escape_time + 1);
 
    }
 
    return 0;
}