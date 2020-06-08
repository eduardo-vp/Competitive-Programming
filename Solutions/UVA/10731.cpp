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

int n,numScc;
int counter;
vector<int> num,low,visited,sc;
stack<int> st;
vector< set<char> > scc,aux;
vector< vector<int> > adj;
map<char,int> getId;
map<int,char> getName;

void dfs(int u){
    visited[u] = 1;
    st.push(u);
    num[u] = low[u] = ++counter;
    FOR(i,0,adj[u].size()){
        int v = adj[u][i];
        if(!num[v])
            dfs(v);
        if(visited[v])
            low[u] = min(low[u],low[v]);
    }
    if(num[u] == low[u]){
        int v;
        set<char> s;
        do{
            v = st.top();
            st.pop();
            sc[v] = numScc;
            s.insert(getName[v]);
            visited[v] = 0;
        }while(v != u);
        numScc++;
        scc.pb(s);
    }
}

int main(){

    int tc = 1;
    while(cin >> n and n){
        if(tc > 1) cout << endl;
        char lets[6];
        int cont = 0;
        adj.assign(5*n,vector<int>());
        scc.clear();
        getId.clear();
        getName.clear();
        FOR(i,0,n){
            FOR(j,0,6){
                cin >> lets[j];
                if(!getId.count(lets[j])) 
                    getId[lets[j]] = cont, getName[cont] = lets[j], cont++;
            }
            FOR(j,0,5){
                if(lets[5] == lets[j]) continue;
                adj[getId[lets[5]]].pb(getId[lets[j]]);
            }
        }
        n = getId.size();
        counter = numScc = 0;
        num.assign(n,0);
        low.assign(n,0);
        visited.assign(n,0);
        sc.assign(n,0);
        FOR(i,0,n)
            if(!num[i]) dfs(i);

        sort(scc.begin(),scc.end());
        FOR(i,0,numScc){
            for(set<char>::iterator it = scc[i].begin(); it != scc[i].end(); ++it){
                if(it != scc[i].begin()) cout << " ";
                cout << *it;
            }
            cout << endl;
        }
        tc++;
    }      

    return 0;
}
