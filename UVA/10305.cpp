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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

stack<int> st;
vector<int> visited;
vector< vector<int> > adj;

void dfs(int u){
    visited[u] = 1;
    FOR(i,0,adj[u].size()){
        int v = adj[u][i];
        if(!visited[v])
            dfs(v);
    }
    st.push(u);
}

int main(){

    int n,m;
    while(cin >> n >> m){
        if(n == 0 and m == 0) break;
        int a,b, in[n+1];
        adj.assign(n+1,vector<int>());
        fill(in,0);
        FOR(i,0,m){
            cin >> a >> b;
            adj[a].pb(b);
            in[b]++;
        }
        visited.assign(n+1,0);
        for(int i = 1; i <= n; ++i)
            if(!visited[i]) dfs(i); 
        cout << st.top(); st.pop();
        while(!st.empty()){
            cout << " " << st.top();
            st.pop();
        }
        cout << endl;
    }    

    return 0;
}
