#include <bits/stdc++.h>
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1000000000
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 2100
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int cont,numScc,num[N],low[N],visited[N];
stack<int> st;
vector< vector<int> > adj;

void dfs(int u){
    num[u] = low[u] = ++cont;
    st.push(u);
    visited[u] = 1;
    FOR(i,0,adj[u].size()){
        int v = adj[u][i];
        if(!num[v])
            dfs(v);
        if(visited[v])
            low[u] = min(low[u],low[v]);
    }
    if(num[u] == low[u]){
        int v;
        do{
            v = st.top();
            st.pop();
            visited[v] = 0;
        }while(u != v);
        numScc++;
    }
}

int main(){

    int n,m;
    while(cin >> n >> m){
        if(n == 0 and m == 0) break;
        int u,v,p;
        adj.assign(n+1,vector<int>());
        FOR(i,0,m){
            cin >> u >> v >> p;
            adj[u].pb(v);
            if(p == 2) adj[v].pb(u);
        }
        cont = numScc = 0;
        FOR(i,0,n+1) num[i] = visited[i] = 0;
        FOR(i,1,n+1)
            if(!num[i]) dfs(i);
        cout << (numScc == 1) << endl;
    }        

    return 0;
}
