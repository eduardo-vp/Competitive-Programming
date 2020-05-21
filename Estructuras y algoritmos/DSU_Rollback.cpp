struct DSUrb {
	vector<int> e;
	void init(int n) { e = vector<int>(n,-1); }
	int get(int x) { return e[x] < 0 ? x : get(e[x]); } 
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	vector<array<int,4>> mod;
	bool unite(int x, int y) { // union-by-rank
		x = get(x), y = get(y); 
		if (x == y) {
			mod.pb({MOD,MOD,MOD,MOD});
			return 0;
		}
		if (e[x] > e[y]) swap(x,y);
		mod.pb({x,y,e[x],e[y]});
		e[x] += e[y]; e[y] = x;
		return 1;
	}
	void rollback() {
		auto a = mod.bk; mod.pop_back();
		if (a[0] != MOD) e[a[0]] = a[2], e[a[1]] = a[3];
	}
};
