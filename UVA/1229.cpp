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
#define N 120
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int n,numScc;
int counter,num[N],low[N],visited[N],sc[N];
stack<int> st;
set<string> ans;
vector<int> scc[N];
vector< vector<int> > adj, inAdj;
map<string,int> getId;
map<int,string> getName;

void dfs(int u){
    num[u] = low[u] = ++counter;
    st.push(u);
    visited[u] = 1;
    FOR(i,0,adj[u].size()){
        int v = adj[u][i];
        if(!num[v]){
            dfs(v);
            low[u] = min(low[u],low[v]);
        }else if(visited[v])
            low[u] = min(low[u],low[v]);
    }
    if(num[u] == low[u]){
        scc[numScc].clear();
        int v;
        //cout << "Getting scc" << endl;
        do{
            v = st.top();
            st.pop();
            visited[v] = 0;
            sc[v] = numScc;
            scc[numScc].pb(v);
        }while(u != v);
        numScc++;
    }
}

void dfsInAdj(int u){
    visited[u] = 1;
    FOR(i,0,inAdj[u].size()){
        int v = inAdj[u][i];
        if(!visited[v]){
            ans.insert(getName[v]);
            //trace(getName[v]);
            dfsInAdj(v);
        }
    }
}

int main(){

    while(cin >> n and n){
        string cad,linea,x;
        getId.clear();
        getName.clear();
        adj.assign(n,vector<int>());
        inAdj.assign(n,vector<int>());
        int cont = 0;
        FOR(i,0,n){
            cin >> cad;
            if(!getId.count(cad)) getId[cad] = cont, getName[cont] = cad, cont++;
            getline(cin,linea);
            istringstream iss(linea);
            set<int> used;
            while(iss >> x){
                if(!getId.count(x)) getId[x] = cont, getName[cont] = x, cont++;
                if(used.count(getId[x])) continue;
                used.insert(getId[x]);
                adj[getId[x]].pb(getId[cad]);
                inAdj[getId[cad]].pb(getId[x]);
            }
        }
        counter = numScc = 0;
        FOR(i,0,n) num[i] = visited[i] = 0;
        FOR(i,0,n)
            if(!num[i]) dfs(i);
        ans.clear();
        FOR(i,0,numScc){
            if( (int(scc[i].size()) > 1) or (int(inAdj[scc[i][0]].size()) == 0) ){
                FOR(j,0,scc[i].size()){
                    ans.insert(getName[scc[i][j]]);
                }
                fill(visited,0);
                dfsInAdj(scc[i][0]);
            }
        }
        cout << ans.size() << endl;
        for(set<string>::iterator it = ans.begin(); it != ans.end(); ++it){
            if(it != ans.begin()) cout << " ";
            cout << *it;
        }
        cout << endl;
    }

    return 0;
}
