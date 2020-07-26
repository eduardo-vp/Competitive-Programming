
struct DSUrb {
	int p[N], rk[N], val[N], cnt;
	int* where[N];
	DSUrb(){ cnt = 0; }
	void reset(int n){
		REP(i,0,n+1) p[i] = i, rk[i] = 1;
		cnt = 0;
	}
	void rollback(){
		while(cnt > 0){
			*where[cnt-1] = val[cnt-1];
			--cnt;
		}
	}
	int getp(int a){
		return (a == p[a] ? a : getp(p[a]));
	}
	void unite(int a, int b){
		a = getp(a), b = getp(b);
		if(a == b) return;
		if(rk[a] < rk[b]) swap(a,b);
		where[cnt] = &rk[a];
		val[cnt++] = rk[a];
		where[cnt] = &p[b];
		val[cnt++] = p[b];
		assert(cnt < N);
		rk[a] += rk[b];
		p[b] = a;
	}
	int getpFast(int a){
		return (a == p[a] ? a : (p[a] = getpFast(p[a])));
	}
	void uniteFast(int a, int b){
		a = getpFast(a), b = getpFast(b);
		if(a == b) return;
		if(rk[a] < rk[b]) swap(a,b);
		rk[a] += rk[b];
		p[b] = a;
	}
};
