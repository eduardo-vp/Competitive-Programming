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

int main(){

    string cad;
    vector<char> ans;
    set<char> seen,used;
    while(getline(cin,cad)){
        if(cad.compare("#") == 0) break;
        if(!used.count(cad[0])){
            used.insert(cad[0]);
            ans.pb(cad[0]);
        }
        FOR(i,1,cad.size()){
            seen.insert(cad[i]);
        }
    }        
    for(set<char>::iterator it = seen.begin(); it != seen.end(); ++it){
        if(!used.count(*it)) ans.pb(*it);
    }

    FOR(i,0,ans.size())
        cout << ans[i];
    cout << endl;

    return 0;
}
