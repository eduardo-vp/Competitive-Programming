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
#define N 50
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int n;
int in[N],dep[N],used[600],visited[600];
set<string> ans;
vector< vector<int> > adj;
vector< vector<char> > lev;
map<int,char> getLet;
map<char,int> getId;

bool reach(int u, int x){
    visited[u] = 1;
    bool ans = false;
    FOR(i,0,adj[u].size()){
        int v = adj[u][i];
        if(x == v) return true;
        else
            ans = ans or reach(v,x);
    }
    return ans;
}

bool valid(string cad){
    FOR(i,0,cad.size()){
        FOR(j,i+1,cad.size()){
            fill(visited,0);
            if(reach(getId[cad[j]],getId[cad[i]])) return false;
        }
    }
    return true;
}

void backtrack(string cad){
    if(cad.size() == n){
        ans.insert(cad);
        return;
    }
    for(int i = 1; i <= n; ++i){
        if(!used[i]){
            used[i] = 1;
            string aux = cad + string(1,getLet[i]);
            if(valid(aux)){
                backtrack(aux);
            }
            used[i] = 0;
        }
    }
}

int main(){

    int tc = 1;
    string linea;
    while(getline(cin,linea)){
        if(linea.compare("") == 0) break;
        if(tc > 1) cout << endl;
        getId.clear();
        getLet.clear();
        char a,b,c; int cont = 1;
        istringstream iss(linea);
        n = 0;
        while(iss >> c)
            getId[c] = cont, getLet[cont] = c, cont++, n++;
        getline(cin,linea);
        ans.clear();
        lev.assign(30,vector<char>());
        adj.assign(getId.size()+1,vector<int>());
        fill(in,0);
        
        istringstream iss2(linea);
        while(iss2 >> a >> b){
            adj[getId[a]].pb(getId[b]);
            in[getId[b]]++;
        }

        fill(used,0);
        backtrack("");
        for(set<string>::iterator it = ans.begin(); it != ans.end(); ++it)
            cout << *it << endl;
        tc++;
    }

    return 0;
}
