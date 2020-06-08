
struct SparseTable{
	int n, flog[N];
	int rmq[N][LGMAX];
	ST(){}
	void build(vector<int> &vec){
		n = sz(vec);
		flog[1] = 0;
		REP(i,2,N) flog[i] = flog[i>>1] + 1;
		for(int i = 0; i < n; ++i)
			rmq[i][0] = vec[i];
		for(int lg = 1, pw = 2; lg < LGMAX; ++lg, pw *= 2){
			for(int i = 0; i < n; ++i){
				if(i+pw/2 < n) rmq[i][lg] = min(rmq[i][lg-1],rmq[i+pw/2][lg-1]);
				else rmq[i][lg] = rmq[i][lg-1];
			}
		}
	}

	int query(int i, int j){
		if(i == j) return rmq[i][0];
		int lg = flog[j-i];
		int pw = (1 << lg);
		return min(rmq[i][lg],rmq[j-pw+1][lg]);
	}
};
