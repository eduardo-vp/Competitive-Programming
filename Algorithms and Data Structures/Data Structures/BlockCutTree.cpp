
typedef pair<int,int> ii;

vector<ii> st; // guarda temporalmente las componentes biconexas
int n, m, gid; 
int art[N]; // art[i]: 0 -> no es punto de articulacion, 1 -> es punto de articulacion 
int num[N],low[N],par[N]; // arreglos para el tarjan
int idBct[N]; // idBct[i]: id de la componente biconexa
vector<int> adj[N]; // grafo original
vector<int> bct[N]; // grafo del block cut tree
vector< pair<ii,int> > bridges; // puentes (arista, id de la arista)
vector< vector<ii> > bcc; // componentes biconexas

inline ii edge(int a, int b) { return ii(min(a, b), max(a, b)); }

void tarjan(int u, bool root = false){
  num[u] = low[u] = gid++;
  int child = 0;
  for(int v : adj[u]) if(v != par[u]) {
    if (num[v] == -1) {
      child++;
      par[v] = u;
      st.push_back(make_pair(u, v));
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if(low[v] > num[u]) bridges.push_back(make_pair(edge(u, v),0));
      if((root and child > 1) or (!root and low[v] >= num[u])){
        // punto de articulacion
        art[u] = 1;
        vector<ii> tmp;
        while(st.back() != make_pair(u,v)) 
          tmp.push_back(st.back()), st.pop_back();
        tmp.push_back(st.back()), st.pop_back();
        bcc.push_back(tmp);
      }
    }else if(num[v] < num[u]){
      low[u] = min(low[u],num[v]);
      st.push_back(make_pair(u,v));
    }
  }
}

void build_block_cut() {
  int cnt = 0;
  for(vector<ii> &vec : bcc){
    int aux = cnt++;
    if(vec.size() == 1){
      (*lower_bound(bridges.begin(), bridges.end(), make_pair(edge(vec[0].first, vec[0].second), -1))).second = aux;
    }
    set<int> s;
    for(ii &p : vec) {
      int a = p.first, b = p.second;
      for(int t = 0; t < 2; ++t){ // run for a and b
        if (art[a]) {
          if (!s.count(a)) {
            if(idBct[a] == -1) idBct[a] = cnt++;
            s.insert(a);
            bct[aux].push_back(idBct[a]);
            bct[idBct[a]].push_back(aux);
          }
        }else idBct[a] = aux;
        swap(a,b);
      }
    }
  }
}

void go(){
  // tarjan
  gid = 0;
  for(int i = 0; i < n; ++i)
    art[i] = 0, par[i] = num[i] = low[i] = -1;
  
  for(int i = 0; i < n; ++i) if(num[i] == -1) {
    tarjan(i, true);
    if(st.size() > 0) bcc.push_back(st);
    st.clear();
  }

  sort(bridges.begin(),bridges.end());
  // construir block-cut tree
  memset(idBct, -1, sizeof(idBct));
  build_block_cut();
}

bool is_bridge(int a, int b) {
  auto it = lower_bound(bridges.begin(), bridges.end(), make_pair(edge(a, b), -1));
  if (it == bridges.end()) return false;
  return (*it).first == edge(a, b);
}

int get_bridge_id(int a, int b) {
  return (*lower_bound(bridges.begin(), bridges.end(), make_pair(edge(a, b), -1))).second;
}

