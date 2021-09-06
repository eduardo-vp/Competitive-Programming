#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define INF 1e9
#define fill(x,v) memset(x,v,sizeof(x))
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int young[1000][1000];
int old[1000][1000];
map<char,int> getId;
map<int,char> getName;

int main(){

  int n;
  while(cin >> n){
    if(n == 0) break;
    char a,b,c,d;
    int w,cont = 0;
    for(int i = 0; i < 1000; i++) 
      for(int j = 0; j < 1000; j++)
        young[i][j] = old[i][j] = INF;
    
    for(int i = 0; i < n; i++){
      cin >> a >> b >> c >> d >> w;
      if(getId.count(c) == 0) getName[cont] = c,getId[c] = cont++;
      if(getId.count(d) == 0) getName[cont] = d,getId[d] = cont++;
      if(a == 'Y'){
        young[getId[c]][getId[d]] = w;
        if(b == 'B') young[getId[d]][getId[c]] = w;
      }else{
        old[getId[c]][getId[d]] = w;
        if(b == 'B') old[getId[d]][getId[c]] = w;
      }
    }
    cin >> a >> b;
    if(getId.count(a) == 0) getName[cont] = a,getId[a] = cont++;
    if(getId.count(b) == 0) getName[cont] = b,getId[b] = cont++;
    for(int i = 0; i < 1000; i++) young[i][i] = old[i][i] = 0;
    //floyd
    for(int k = 0; k < cont; k++)
      for(int i = 0; i < cont; i++)
        for(int j = 0; j < cont; j++){
          young[i][j] = min(young[i][j],young[i][k] + young[k][j]);
          old[i][j] = min(old[i][j],old[i][k] + old[k][j]);         
        }

    int ans = INF;
    int s = getId[a], dest = getId[b];
    vector<char> cit;
    for(int i = 0; i < cont; i++){
      if(young[s][i] + old[dest][i] < ans){
        cit.clear();
        ans = young[s][i] + old[dest][i];
      }
      if(young[s][i] + old[dest][i] == ans)
        cit.pb(getName[i]);
    }
    if(ans == INF){
      cout << "You will never meet." << endl;
    }else{
      cout << ans << " ";
      cout << cit[0];
      for(int i = 1; i < int(cit.size()); i++)
        cout << " " << cit[i];
      cout << endl;
    }
    getId.clear();
    getName.clear();
  }

  return 0;
}