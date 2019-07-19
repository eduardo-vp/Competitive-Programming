
/* TAP Police Query */

#include <bits/stdc++.h>
#include <sys/resource.h>
#define N 1010000
#define LGMAX 25
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

/* Start Block Cut Tree */

int P[N][LGMAX];
vector<ii> st;
int n,m,gid,art[N],num[N],low[N],par[N],idBct[N];
vector<int> adj[N];
vector<int> bct[N]; // bct = block cut tree
vector< pair<ii,int> > bridges;
vector< vector<ii> > bcc;

inline ii edge(int &a, int &b){ return ii(min(a,b),max(a,b)); }

void Tarjan(int u, bool root = false){
	num[u] = low[u] = gid++;
	int child = 0;
	for(int v : adj[u]) if(v != par[u]){
		if(num[v] == -1){
			child++;
			par[v] = u;
			st.push_back(make_pair(u,v));
			Tarjan(v);
			low[u] = min(low[u],low[v]);
			if(low[v] > num[u]) bridges.push_back(make_pair(edge(u,v),0));
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

void BuildBlockCut(){
	int cnt = 0;
	for(vector<ii> &vec : bcc){
		int aux = cnt++;
		if(vec.size() == 1){
			
			(*lower_bound(bridges.begin(),bridges.end(),make_pair(edge(vec[0].first,vec[0].second),-1))).second = aux;
		}
		set<int> s;
		for(ii &p : vec){
			int a = p.first, b = p.second;
			if(art[a]){
				if(idBct[a] == -1){
					s.insert(a);
					idBct[a] = cnt++;
					bct[aux].push_back(idBct[a]);
					bct[idBct[a]].push_back(aux);
				}else if(!s.count(a)){
					s.insert(a);
					bct[aux].push_back(idBct[a]);
					bct[idBct[a]].push_back(aux);
				}
			}else idBct[a] = aux;
			if(art[b]){
				if(idBct[b] == -1){
					s.insert(b);
					idBct[b] = cnt++;
					bct[aux].push_back(idBct[b]);
					bct[idBct[b]].push_back(aux);
				}else if(!s.count(b)){
					s.insert(b);
					bct[aux].push_back(idBct[b]);
					bct[idBct[b]].push_back(aux);
				}
			}else idBct[b] = aux;
		}
	}
}

void Go(){
	// Tarjan
	gid = 0;
	for(int i = 0; i < n; ++i)
		art[i] = 0, par[i] = num[i] = low[i] = -1;
	
	for(int i = 0; i < n; ++i) if(num[i] == -1){
		Tarjan(i,true);
		if(st.size() > 0) bcc.push_back(st);
		st.clear();
	}

	sort(bridges.begin(),bridges.end());
	// construir block-cut tree
	memset(idBct,-1,sizeof(idBct));
	BuildBlockCut();
}

/* End Block Cut Tree */

int tin[N],tout[N],dep[N];

bool ancestor(int a, int b){ 
	return tin[b] >= tin[a] and tout[b] <= tout[a]; 
}

int __lca(int a, int b){
	if(dep[a] > dep[b]) swap(a,b);
	for(int j = LGMAX-1; j >= 0; --j)
		if(dep[b] - (1<<j) >= dep[a])
			b = P[b][j];
	if(a == b) return a;
	for(int j = LGMAX-1; j >= 0; --j)
		if(P[a][j] != P[b][j])
			a = P[a][j], b = P[b][j];
	return P[a][0];
}

void dfs(int u, int p = -1, int d = 0){
	tin[u] = gid++;
	P[u][0] = p;
	dep[u] = d;
	for(int j = 1; j < LGMAX; ++j)
		if(P[u][j-1] != -1)
			P[u][j] = P[P[u][j-1]][j-1];
	for(int v : bct[u]) if(v != p)
		dfs(v,u,d+1);
	tout[u] = gid++;
}

bool isBridge(int a, int b){
	vector< pair<ii,int> >::iterator it = lower_bound(bridges.begin(),bridges.end(),make_pair(edge(a,b),-1));
	if(it == bridges.end()) return false;
	return (*it).first == edge(a,b);
}

bool isLeaf(int a, int b){
	return adj[a].size() == 1 or adj[b].size() == 1;
}

bool onPath(int a, int c, int b){
	return ancestor(a,c) and ancestor(c,b);
}

int getBridgeId(int a, int b){
	return (*lower_bound(bridges.begin(),bridges.end(),make_pair(edge(a,b),-1))).second;
}

int main(){

	const rlim_t kStackSize = 64L * 1024L * 1024L;
	struct rlimit rl;
	int result;
	result = getrlimit(RLIMIT_STACK,&rl);
	if(result == 0){
		if(rl.rlim_cur < kStackSize){
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK,&rl);
			if(result != 0){
				fprintf(stderr,"setrlimit returned result = %d\n",result);
			}
		}
	}

	int q,t,a,b,c,d;
	scanf("%d %d",&n,&m);
	for(int i = 0; i < m; ++i){
		scanf("%d %d",&a,&b);
		// indexar en cero
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	Go();
	
	gid = 0;
	dfs(0);
	/* Responder queries */
	scanf("%d",&q);
	while(q--){
		scanf("%d",&t);
		if(t == 1){
			scanf("%d %d %d %d",&a,&b,&c,&d);
			a--; b--; c--; d--;
			if(isBridge(c,d)){
				if(isLeaf(c,d)){
					if( (adj[c].size() == 1) and (a == c or b == c) ) 
						printf("ne\n");
					else if( (adj[d].size() == 1) and (a == d or b == d) ) 
						printf("ne\n");
					else printf("da\n");
				}else{
					int u = idBct[a], v = idBct[b]; 
					int w = getBridgeId(c,d), lca = __lca(u,v);
					if(onPath(lca,w,u) or onPath(lca,w,v)) printf("ne\n");
					else printf("da\n");
				}
			}else printf("da\n");
		}else{
			scanf("%d %d %d",&a,&b,&c);
			a--; b--; c--;
			if(art[c]){
				int u = idBct[a], v = idBct[b], w = idBct[c], lca = __lca(u,v);
				if(onPath(lca,w,u) or onPath(lca,w,v)) printf("ne\n");
				else printf("da\n");
			}else printf("da\n");
		}
	}

	return 0;
}
