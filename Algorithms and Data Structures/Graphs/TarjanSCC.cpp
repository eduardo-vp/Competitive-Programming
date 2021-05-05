int comp[N];
vector<int> nodes[N];
vector<int> adj[N];

int tarjan(int n){
	int gid = 1, scc = 0;
	vector<int> num(n, 0), low(n, 0), vist(n, 0), stk;
	function<void(int)> dfs = [&](int u){
		num[u] = low[u] = gid++;
		stk.push_back(u);
		vist[u] = 1;
		for(int v : adj[u]){
			if(num[v] == 0) dfs(v);
			if(vist[v]) low[u] = min(low[u],low[v]);
		}
		if(num[u] == low[u]){
			int v; do{
				v = stk.back(); stk.pop_back(); vist[v] = 0;
				nodes[scc].push_back(v);
			}while(u != v);
			scc++;
		}
	};
	for(int i = 0; i < n; ++i){
		if(!num[i]) dfs(i);
	}
	return scc;
}
