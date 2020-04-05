struct TwoSat {
	int N;
	vector< vector<int> > gr;
	vector<int> values;
	
	TwoSat(int n = 0) : N(n), gr(2*n) {}
	
	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f^1].push_back(j);
		gr[j^1].push_back(f);
	}
	
  int time = 0;
	vector<int> val, comp, z; 
	int dfs(int i) {
		int low = val[i] = ++time, x; 
    z.push_back(i);
		for(int e : gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		++ time;
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = time;
			if (values[x>>1] == -1)
				values[x>>1] = !(x & 1);
		} while (x != i);
		return val[i] = low;
	}
	
	bool solve() {
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		REP(i,0,2*N) if (!comp[i]) dfs(i);
		REP(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};
