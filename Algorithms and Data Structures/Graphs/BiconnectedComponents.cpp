
int gid;
int num[N], low[N], par[N], art[N];
vector<int> adj[N];
vector<ii> stk, bridges;
vector< vector<ii> > bcc;

void tarjan(int u, bool root = false){
	num[u] = low[u] = gid++;
	int child = 0;
	for(int v : adj[u]) if(v != par[u]){
		if(num[v] == -1){
			child++;
			par[v] = u;
			stk.push_back(make_pair(u,v));
			tarjan(v);
			low[u] = min(low[u], low[v]);
			// check bridge
			if(low[v] > num[u]) bridges.push_back(make_pair(u,v));
			// check articulation point
			if((root && child > 1) || (!root && low[v] >= num[u])){
				art[u] = 1;
				vector<ii> tmp;
				while(stk.back() != make_pair(u,v)){
					tmp.push_back(stk.back()); 
					stk.pop_back();
				}
				tmp.push_back(stk.back());
				stk.pop_back();
				bcc.push_back(tmp);
			}
		}else if(num[v] < num[u]){
			low[u] = min(low[u], num[v]);
			stk.push_back(make_pair(u,v));
		}
	}
}

void run_bcc(int n){
	gid = 0;
	for(int i = 0; i < n; ++i){
		art[i] = 0;
		par[i] = num[i] = low[i] = -1;
	}
	for(int i = 0; i < n; ++i) if(num[i] == -1){
		tarjan(i, true);
		if(stk.size() > 0) bcc.push_back(stk);
		stk.clear();
	}
}
