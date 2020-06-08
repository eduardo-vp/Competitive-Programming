#include <bits/stdc++.h>

#define INF 1e9
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); i++)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 10100

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

ll n,m,a;
ll p[N],rk[N];
ll air, cost;

void init(){ FOR(i,1,n+1) p[i] = i, rk[i] = 0; }
int findSet(int i){ return (p[i] == i) ? (i) : (p[i] = findSet(p[i])); }
bool isSameSet(int i, int j){ return findSet(i) == findSet(j); }
void unionSet(int i, int j){
    int x = findSet(i), y = findSet(j);
    if(rk[x] > rk[y]) p[y] = x;
    else{
        p[x] = y;
        if(rk[x] == rk[y]) rk[y]++;
    }
}

vector<iii> edges;

void kruskal(){
    sort(edges.begin(),edges.end());
    init();
    FOR(i,0,m){
        int w = edges[i].fst , x = edges[i].snd.fst, y = edges[i].snd.snd;
        if(!isSameSet(x,y) and w < a){
            unionSet(x,y);
            air--;
            cost += w;
        }
    }
}

int main(){

    ll tc;
    cin >> tc;
    FOR(TC,0,tc){
        cin >> n >> m >> a;
        //trace(n); trace(m); trace(a);
        int x,y,z;
        FOR(i,0,m){
            cin >> x >> y >> z;
            edges.pb(mp(z,ii(x,y)));
        }
        air = n;
        cost = 0;
        kruskal();
        cost += air*a;
        edges.clear();
        printf("Case #%d: %lld %lld\n",TC+1,cost,air);
    }

    return 0;
}