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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int s,t,c;
int maxflow,flow;
int res[105][105],dist[105],p[105];

void augment(int x, int minEdge){
    if(x == s){ flow = minEdge; }
    else if(p[x] != -1){
        augment(p[x],min(minEdge,res[p[x]][x]));
        res[p[x]][x] -= flow;
        res[x][p[x]] += flow;
    }
}

int main(){

    int n,x,y,cost; 
    int tc = 1;
    while(cin >> n and n){
        cin >> s >> t >> c;
        fill(res,0);
        FOR(i,0,c){
            cin >> x >> y >> cost;
            res[x][y] += cost;
            res[y][x] += cost;
        }
        maxflow = 0;
        while(1){
            flow = 0;
            fill(dist,-1); fill(p,-1);
            queue<int> q; q.push(s); dist[s] = 0;
            while(!q.empty()){
                int u = q.front(); q.pop();
                if(u == t) break;
                for(int i = 1; i <= n; i++){
                    int v = i;
                    if(res[u][v] > 0 and dist[v] == -1)
                        dist[v] = dist[u]+1, q.push(v), p[v] = u;
                }
            }
            augment(t,INT_MAX);
            if(flow == 0) break;
            maxflow += flow;
        }
        cout << "Network " << tc++ << endl;
        cout << "The bandwidth is " << maxflow << "." << endl;
        cout << endl;
    }

    return 0;
}