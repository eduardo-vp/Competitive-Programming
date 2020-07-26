
// N maximum number of nodes
// LG >= log(N)

int dep[N];
int P[N][LG];

int __lca(int a, int b){
	if(dep[a] < dep[b]) swap(a,b);
	for(int j = LG-1; j >= 0; --j)
		if( dep[a]-(1<<j) >= dep[b] )
			a = P[a][j];
	if(a == b) return a;
	for(int j = LG-1; j >= 0; --j)
		if(P[a][j] != P[b][j])
			a = P[a][j], b = P[b][j];
	return P[a][0];
}

int get_dist(int a, int b){
	int lca = __lca(a,b);
	return dep[a] + dep[b] - 2 * dep[lca];
}

void dfs(int u, int p = -1, int d = 0){
	dep[u] = d;
	P[u][0] = p;
	for(int i = 1; i < LG && P[u][i-1] >= 0; ++i){
		P[u][i] = P[P[u][i-1]][i-1];
	}
	for(int v : adj[u]) if(v != p){
		dfs(v,u,d+1);
	}
}

// returns the k-th node in the path from u to v (0-indexed) 
int get_kth(int u, int v, int lca, int k){
	int d = dep[u] - dep[lca];
	if(k <= d){
		for(int i = LG-1; i >= 0; --i){
			if(k - (1 << i) >= 0){
				k -= (1 << i);
				u = P[u][i];
			}
		}
		return u;
	}
	int dd = dep[u] + dep[v] - 2*dep[lca];
	return get_kth(v,u,lca,dd-k);
}

int main(){
	
	// read graph
	memset(P,-1,sizeof(P));
	dfs(root);
	
	return 0;	
}
