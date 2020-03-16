
// Call ac(n) to check if it's a chordal graph
// Array pos[N] has the Perfect elimination order if true

struct ChordGraph{
	vector<int> adj[N], a[N];
	int qu[N], pos[N], l[N], r[N], c[N];
	bool ac(int n) {
		iota(qu, qu+n, 0);
		iota(pos, pos+n, 0);
		memset(l, 0, 4*n);
		r[0]=n-1;
		memset(c, 0, 4*n);
		for(int i = n-1; i >= 0; --i) {
			int u = qu[i];
			--r[l[i]];
			vector<array<int, 2>> z;
			for(int v : adj[u]) {
				if(pos[v] > i) continue;
				int lc = l[pos[v]];
				z.push_back({r[lc]-c[lc]++, r[lc]});
			}
			for(int v : adj[u]) {
				if(pos[v] > i) continue;
				int np = r[l[pos[v]]]--;
				pos[qu[np]] = pos[v];
				swap(qu[pos[v]], qu[np]);
				l[np] = np-(--c[l[pos[v]]]);
				pos[v] = np;
			}
			for(array<int, 2> a : z)
				r[a[0]] = a[1];
			int w = -1;
			for(int v : adj[u])
				if(pos[v]>i && (w<0 || pos[v]<pos[w]))
					w=v;
			if(w >= 0)
				a[w].push_back(u);
		}
		for(int i = 0; i < n; ++i) {
			for(int j : adj[i])
				c[j]=1;
			for(int j : a[i])
				for(int k : adj[j])
					if(pos[k]>pos[i] && !c[k])
						return 0;
			for(int j : adj[i])
				c[j]=0;
		}
		return 1;
	}
};
