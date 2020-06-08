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
#define N 10000
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

stack<int> st;
int numScc,cont,num[N],low[N],visited[N];
vector< vector<int> > adj;
map<string,int> getId;

void dfs(int u){
    visited[u] = 1;
    num[u] = low[u] = ++cont;
    st.push(u);
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
        }while(v != u);
        numScc++;
    }
}

int main(){

    int n,m;
    while(cin >> n >> m){
        if(n == 0 and m == 0) break;
        cin.ignore();
        string cad1,cad2;
        adj.assign(n,vector<int>());
        getId.clear();
        int counter = 0;
        FOR(i,0,n){
            getline(cin,cad1);
            getId[cad1] = counter++;
        }
        FOR(i,0,m){
            getline(cin,cad1);
            getline(cin,cad2);
            adj[getId[cad1]].pb(getId[cad2]);
        }
        numScc = cont = 0;
        FOR(i,0,n) num[i] = visited[i] = 0;
        FOR(i,0,n)
            if(!num[i]) dfs(i);
        cout << numScc << endl;
    }

    return 0;
}
