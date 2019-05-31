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
#define N 300
using namespace std;

int n,l;
int zeros,ones,res;
int color[N];
vector<int> adj[N];

bool has(vector<int> v, int e){
    FOR(i,0,v.size())
        if(v[i] == e) return true;
    return false;
}

bool dfs(int x){
    bool bip = true;
    FOR(i,0,adj[x].size()){
        int v = adj[x][i];
        if(color[v] == color[x]) bip = false;
        if(color[v] == -1){
            color[v] = 1 - color[x];
            if(color[v]) ones++;
            else zeros++;
            if(!dfs(v)) bip = false;
        }
    }
    return bip;
}

void check(){
    fill(color,-1);
    res = 0;
    for(int i = 0; i < n; i++){
        if(color[i] == -1){
            color[i] = ones = 0;
            zeros = 1;
            if(dfs(i))
                res += max(zeros,ones);
        }
    }
}

int main(){

    fastio;

    int tc;
    cin >> tc;
    int TC = 1;
    while(tc--){
        cin >> n;
        FOR(i,0,n){
            int m; cin >> m;
            FOR(j,0,m){
                int x; cin >> x;
                x--;
                if(x < n){
                    if(!has(adj[i],x))
                        adj[i].pb(x);
                    if(!has(adj[x],i))
                        adj[x].pb(i);
                }
            }
        }
        check();
        cout << res << endl;
        FOR(i,0,N) adj[i].clear();
    }

    return 0;
}