
struct HLD{
  	STree st;
	int gid,p[N],dep[N],tsz[N],id[N],rt[N];
	int mksz(int u, int pai = -1, int d = 0){
		p[u] = pai; dep[u] = d; tsz[u] = 1;
		for(int v : adj[u]) if(v != pai){
			tsz[u] += mksz(v,u,d+1);
		}
		return tsz[u];
	}
	void dfs(int u, int root = 1){
		id[u] = gid++;
		rt[u] = root;
		int w = 0, wsz = -1;
		for(int v : adj[u]) if(v != p[u] && tsz[v] > wsz){
			w = v;
			wsz = tsz[v];
		}
		if(w) dfs(w,root);
		for(int v : adj[u]) if(v != p[u] && v != w){
			dfs(v,v);
		}
	}
	void modify(int u, int val){
		int idx = id[u];
		st.update(idx,val);
	}
	int query(int u, int v){
		int ans = 0;
		while(rt[u] != rt[v]){
			if(dep[rt[u]] > dep[rt[v]]) swap(u,v);
			ans = max(ans,st.query(id[rt[v]],id[v]+1));
			v = p[rt[v]];
		}
		int a = id[u], b = id[v];
		if(a > b) swap(a,b);
		ans = max(ans,st.query(a,b+1));
		return ans;
	}
	void init(int n){
		gid = 0;
		mksz(1);
		dfs(1);
    		st.init(n);
	}
};
