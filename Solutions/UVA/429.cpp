#include <bits/stdc++.h>
#define INF INT_MAX
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;
typedef vector<int> vi;

vi dist;
queue<int> cola;
vector< vi > g;
map<string,int> getId;
map<int,string> getName;

void test(int x){ cout << "HOLI" << x << endl;}

bool dif(string cad1, string cad2){
  if(cad1.size() != cad2.size()) return false;
  int cont = 0;
  for(int i = 0; i < int(cad1.size()); i++){
    if(cad1[i] != cad2[i]) 
      cont++;
    if(cont > 1) return false;
  }
  return true;
}

void bfs(){
  while(!cola.empty()){
    int u = cola.front(); cola.pop();
    for(int i = 0; i < int(g[u].size()); i++){
      int v = g[u][i];
      if(dist[v] == INF){
        dist[v] = dist[u]+1;
        cola.push(v);
      }
    }
  }
}

int main(){

  int tc;
  bool line = false;
  cin >> tc;
  cin.ignore(); cin.ignore();
  while(tc--){
    if(!line) line = true;
    else cout << endl;
    string cad;
    vector<string> words;
    int cont = 0;
    while(cin >> cad and (cad.compare("*") != 0)){
      words.pb(cad);
      getName[cont] = cad;
      getId[cad] = cont++;
    }
    g.assign(cont,vi());
    cin.ignore();
    for(int i = 0; i < cont-1; i++)
      for(int j = i+1; j < cont; j++)
        if(dif(words[i],words[j])){
          g[i].pb(j); g[j].pb(i);
        }

    while(getline(cin,cad) and (cad.compare("") != 0)){
      istringstream iss(cad);
      string cad1,cad2;
      iss >> cad1 >> cad2;
      dist.assign(cont,INF); dist[getId[cad1]] = 0;
      cola.push(getId[cad1]);
      bfs();
      cout << cad1 << " " << cad2 << " " << dist[getId[cad2]] << endl;
    }
    getId.clear(); getName.clear();
  }

  return 0;
}