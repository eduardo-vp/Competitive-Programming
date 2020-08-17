
long long divide_and_conquer(){
	for(int i = 0; i < n; ++i){
		dp[0][i] = INF;
		old_opt[i] = 0;
	}
	for(int j = 1; j <= k; ++j){
		for(int i = 0; i < n; ++i){
			dp[j&1][i] = INF;
			for(int x = old_opt[i]; x <= i; ++x){
				ll op2 = cost[x][i];
				if(x > 0) op2 += dp[(j-1)&1][x-1];
				if(op2 < dp[j&1][i]){
					old_opt[i] = x;
					dp[j&1][i] = op2;
				}
			}
		}
	}
	return dp[k&1][n-1];
}
