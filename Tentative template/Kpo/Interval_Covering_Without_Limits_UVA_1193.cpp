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
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
void solve(int cnt);
int n, d;
int ans;
int cnt;
struct node
{
    int x, y;
    double l, r;
}island[1010];
bool cmp(const node a, const node b)
{
    return a.x < b.x;
}
void input()
{
    int T = 0;
    while (cin >> n >> d && (n || d))
    {
        bool flag = 0;
        T++;
        for (int i = 1; i <= n; i++)
        {
            cin >> island[i].x >> island[i].y;
            if (island[i].y > d)
                flag = 1;
        }
        if (flag)
            cout << "Case " << T << ": -1\n";
        else
            solve(T);
    }
}
inline double dis(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
void solve(int cnt)
{
    ans = 1;
    sort(island + 1, island + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        island[i].l = (double)island[i].x - sqrt(double(d * d) - double(island[i].y * island[i].y));
        island[i].r = (double)island[i].x + sqrt(double(d * d) - double(island[i].y * island[i].y));
    }
    double last = island[1].r;
    for (int i = 2; i <= n; i++)
    {
        if (island[i].l - last > 1e-6)
        {
            ans++;
            last = island[i].r;
        }
        else if (island[i].r - last < 1e-6)
            last = island[i].r;
    }
    cout << "Case " << cnt << ": " << ans << "\n";
}
int main()
{
    input();
    return 0;
}