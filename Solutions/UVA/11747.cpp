#include <bits/stdc++.h>

#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n,m,x,y,z,p[1050],rk[1050];
vi ans;
vector<iii> edges;

int find(int x){ return (p[x] == x) ? x : (find(p[x])); }
bool isSameSet(int x, int y){ return find(x) == find(y); }
void unionSet(int i, int j){
  int x = find(i), y = find(j);
  if(rk[x] > rk[y]) p[y] = x;
  else{
    p[x] = y;
    if(rk[x] == rk[y]) rk[y]++;
  }
}

void kruskal(){
  sort(edges.begin(),edges.end());
  for(int i = 0; i < m; i++){
    int x = edges[i].second.first, y = edges[i].second.second;
    if(!isSameSet(x,y)){
      unionSet(x,y);
    }else ans.pb(edges[i].first);
  }
}

int main(){

  while(cin >> n >> m){
    if(n == 0 and m == 0) break;
    for(int i = 0; i < m; i++){
      cin >> x >> y >> z;
      edges.pb(mp(z,ii(x,y)));
    }
    for(int i = 0; i < n; i++) p[i] = i;
    fill(rk,0);
    kruskal();
    if((int)ans.size() > 0){
      for(int i = 0; i < (int)ans.size(); i++){
        cout << ans[i];
        if(i < int(ans.size()-1) ) cout << " ";
      }
      cout << endl;
    }else cout << "forest" << endl;
    edges.clear();
    ans.clear();
  }

  return 0;
}