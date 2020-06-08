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

int n,m,cont;
bool pos;
stack<int> st;
vector<int> num,low,visited,ans;
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

void tarjan(int u){
    st.push(u);
    num[u] = low[u] = ++cont;
    visited[u] = 1;
    FOR(i,0,adj[u].size()){
        int v = adj[u][i];
        if(!num[v])
            tarjan(v);
        if(visited[v])
            low[u] = min(low[u],low[v]);
    }
    if(num[u] == low[u]){
        int v,elems = 0;
        do{
            v = st.top();
            st.pop();
            visited[v] = 0;
            elems++;
        }while(u != v);
        pos = pos and (elems == 1);
    }
}

int main(){

    while(cin >> n >> m){
        if(n == 0 and m == 0) break;
        adj.assign(n+1,vector<int>());
        int a,b, in[n+1];
        fill(in,0);
        FOR(i,0,m){
            cin >> a >> b;
            adj[a].pb(b);
            in[b]++;
        }
        pos = true;
        cont = 0;
        num.assign(n+1,0); low.assign(n+1,0); visited.assign(n+1,0);
        for(int i = 1; i <= n; ++i)
            if(!num[i]) tarjan(i);

        if(pos){
            ans.clear();
            visited.assign(n+1,0);
            for(int i = 1; i <= n and pos; ++i)
                if(!in[i]) dfs(i);
            while(!st.empty()){
                cout << st.top() << endl;
                st.pop();
            }
        }else{
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
