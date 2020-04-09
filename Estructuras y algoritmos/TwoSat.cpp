struct TwoSat{
	int n;
	vector< vector<int> > adj;
	vector<int> values;

	TwoSat(int n) : n(n), adj(2*n){}

	void either(int x, int y){
		x = max(2*x, -(2*x+1));
		y = max(2*y, -(2*y+1));
		adj[x^1].pb(y);
		adj[y^1].pb(x);
	}

	int time = 0;
	vector<int> val,comp,z;
	int dfs(int u){
		int low = val[u] = ++time, x;
		z.pb(u);
		for(int v : adj[u]) if(!comp[v])
			low = min(low,val[v] ?: dfs(v));
		++time;
		if(low == val[u]) do{
			x = z.back(); z.pop_back();
			comp[x] = time;
			if(values[x >> 1] == -1)
				values[x >> 1] = !(x & 1);
		}while(x != u);
		return val[u] = low;
	}

	bool solve(){
		values.assign(n,-1);
		val.assign(2*n,0); comp = val;
		REP(i,0,2*n) if(!comp[i]) dfs(i);
		REP(i,0,n) if(comp[2*i] == comp[2*i+1]) return false;
		return true;
	}

};
