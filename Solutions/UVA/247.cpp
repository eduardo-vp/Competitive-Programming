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
#define N 30
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int n,m, numScc;
int counter, num[N], low[N], sc[N], visited[N];
stack<int> st;
vector<int> scc[N];
vector< vector<int> > adj;
map<string,int> getId;
map<int,string> getName;

void dfs(int u){
    st.push(u);
    visited[u] = 1;
    num[u] = low[u] = ++counter;
    FOR(i,0,adj[u].size()){
        int v = adj[u][i];
        if(!num[v]){
            dfs(v);
            low[u] = min(low[u],low[v]);
        }else if(visited[v])
            low[u] = min(low[u],low[v]);
    }
    if(num[u] == low[u]){
        int v;
        scc[numScc].clear();
        //cout << "New Scc" << endl;
        do{
            v = st.top();
            st.pop();
            sc[v] = numScc;
            visited[v] = 0;
            scc[numScc].pb(v);
        }while(u != v);
        numScc++;
    }
}

int main(){

    int tc = 1;
    while(cin >> n >> m and n and m){
        if(tc > 1) cout << endl;
        string cad1,cad2;
        int cont = 0;
        adj.assign(n,vector<int>());
        getId.clear();
        getName.clear();
        FOR(i,0,m){
            cin >> cad1 >> cad2;
            if(!getId.count(cad1)) getId[cad1] = cont, getName[cont] = cad1, cont++;
            if(!getId.count(cad2)) getId[cad2] = cont, getName[cont] = cad2, cont++;
            adj[getId[cad1]].pb(getId[cad2]);
        }
        numScc = counter = 0;
        FOR(i,0,n) num[i] = visited[i] = 0;
        FOR(i,0,n)
            if(!num[i]) dfs(i);

        cout << "Calling circles for data set " << tc++ << ":" << endl;
        FOR(i,0,numScc){
            FOR(j,0,scc[i].size()){
                if(j > 0) cout << ", ";
                cout << getName[scc[i][j]];
            }
            cout << endl;
        }
    }

    return 0;
}
