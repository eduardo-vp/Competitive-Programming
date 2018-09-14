  


int __lca(int a, int b){
	if(dep[a] < dep[b]) swap(a,b);
	for(int j = LG-1; j >= 0; --j)
		if( dep[a]-(1<<j) >= dep[b] )
			a = p[a][j];
	if(a == b) return a;
	for(int j = LG-1; j >= 0; --j)
		if(p[a][j] != p[b][j])
			a = p[a][j], b = p[b][j];
	return pai[a];
}

int dist(int a, int b){
	int lca = __lca(a,b);
	return dep[a] + dep[b] - 2 * dep[lca];
}

void build(){
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < LG; ++j)
			p[i][j] = -1;
	
	for(int i = 1; i <= n; ++i)
		p[i][0] = pai[i];
	
	for(int j = 1; j < LG; ++j)
		for(int i = 1; i <= n; ++i)
			if(p[i][j-1] != -1)
				p[i][j] = p[p[i][j-1]][j-1];
}
