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

int in[N];
vector<int> ans;
vector< vector<int> > adj;
string getName[N];
map<string,int> getId;

int main(){


    int tc = 1,n,m;
    while(cin >> n){
        string cad1,cad2;
        ans.clear();
        getId.clear();
        adj.assign(n,vector<int>());
        FOR(i,0,n){
            cin >> cad1;
            getId[cad1] = i;
            getName[i] = cad1;
        }
        fill(in,0);
        cin >> m;
        FOR(i,0,m){
            cin >> cad1 >> cad2;
            adj[getId[cad1]].pb(getId[cad2]);
            in[getId[cad2]]++;
        }

        priority_queue<int,vector<int>,greater<int> > q;
        for(int i = 0; i < n; ++i)
            if(!in[i]) q.push(i);
        while(!q.empty()){
            int u = q.top();
            q.pop();
            ans.pb(u);
            FOR(i,0,adj[u].size()){
                int v = adj[u][i];
                in[v]--;
                if(!in[v])
                    q.push(v);
            }
        }
        cout << "Case #" << tc++ << ": Dilbert should drink beverages in this order:";
        FOR(i,0,n)
            cout << " " << getName[ans[i]];
        cout << "." << endl << endl;
    }

    return 0;
}
