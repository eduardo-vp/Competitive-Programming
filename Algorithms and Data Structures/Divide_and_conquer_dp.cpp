
// general case
void go(int id, int l, int r, int optl, int optr){
  if(l >= r) return;
  int mid = (l + r) >> 1, opt = -1;
  int od = 1 - id; // other index (previous index)
  ll best = LLONG_MAX, dpcost;
  int lim = min(optr,mid) + 1;
  for(int k = optl; k < lim; ++k){
    dpcost = dp[od][k] + cost[mid][k+1];
    if(dpcost < best){
      best = dpcost; opt = k;
    }
  }
  dp[id][mid] = best;
  go(id,l,mid,optl,opt);
  go(id,mid+1,r,opt,optr);
}

//  only if opt[j-1][i] <= opt[j][i] <= opt[j][i+1]
long long divide_and_conquer(){
  vector<int> old_opt(n,0);
  // dp is [2][n]
  for(int i = 0; i < n; ++i){
    dp[0][i] = 1e18;
  }
  for(int j = 1; j <= k; ++j){
    for(int i = n-1; i >= 0; --i){
      dp[j&1][i] = 1e18;
      int lim = (i+1 < n) ? old_opt[i+1] : n-1;
      for(int cut = old_opt[i]; cut <= lim; ++cut){
        ll dpcost = cost[cut][i];
        if(cut > 0) dpcost += dp[(j-1)&1][cut-1];
        if(dpcost < dp[j&1][i]){
          old_opt[i] = cut;
          dp[j&1][i] = dpcost;
        }
      }
    }
  }
  return dp[k&1][n-1];
}
