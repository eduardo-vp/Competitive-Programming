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
struct node {
    int st;
    int en;
    int mid;
    ll value;
};
 
node tree[4 * MAXN];
ll lazy[4 * MAXN];
 
void init_tree(int index, int left, int right) {
 
    tree[index].st = left, tree[index].en = right;
    tree[index].mid = (tree[index].st + tree[index].en) >> 1;
 
    if (tree[index].st != tree[index].en) {
        init_tree(2 * index, left, tree[index].mid);
        init_tree(2 * index + 1, tree[index].mid + 1, right);
    }
 
    tree[index].value = lazy[index] = 0;
}
 
ll getValue(int index) {
    return tree[index].value + (lazy[index] * (ll) (tree[index].en - tree[index].st + 1));
}
 
void refresh(int index) {
    lazy[2 * index] += lazy[index];
    lazy[2 * index + 1] += lazy[index];
    lazy[index] = 0;
}
 
void update(int index, int left, int right, int value) {
    //si está en el intervalo indicado
    if (tree[index].st >= left && tree[index].en <= right) {
        lazy[index] += value;
        return;
    }
    //si no esta
    if (tree[index].st > right || tree[index].en < left)
        return;
    if (tree[index].st < left || tree[index].en > right) {
        refresh(index);//lazy propagation
        update(2 * index, left, right, value);
        update(2 * index + 1, left, right, value);
        //combine
        tree[index].value = getValue(2 * index) + getValue(2 * index + 1);
        // debug(index);
        // debug(tree[index].value);
    }
}
 
ll query(int index, int left, int right) {
    if (tree[index].st >= left && tree[index].en <= right)
        return getValue(index);
    if (tree[index].st > right || tree[index].en < left)
        return 0;
    ll result = 0;
    if (tree[index].st < left || tree[index].en > right) {
        refresh(index);
        result = query(2 * index, left, right) + query(2 * index + 1, left, right);
        tree[index].value = getValue(2 * index) + getValue(2 * index + 1);
    }
    return result;
}
 
 
int main(int argc, char **args) {
    int T, p, q, v;
    scanf("%d", &T);
    while (T-- > 0) {
        int n,c;
        scanf("%d", &n);
        scanf("%d", &c);
        init_tree(1, 0, n - 1);
        f(i,0,c) {
            scanf("%d", &n);
            if (n == 0) {
                scanf("%d%d%d", &p, &q, &v);
                update(1, p - 1, q - 1, v);
            } else {
                scanf("%d%d", &p, &q);
                printf("%lld\n", query(1, p - 1, q - 1));
            }
        }
    }
    return 0;
}