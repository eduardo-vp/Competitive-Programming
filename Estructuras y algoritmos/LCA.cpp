  


void process3(int N, int T[MAXN], int P[MAXN][LOGMAXN]){
      int i, j;
  //we initialize every element in P with -1
      for (i = 0; i < N; i++)
          for (j = 0; 1 << j < N; j++)
              P[i][j] = -1;
  //the first ancestor of every node i is T[i]
      for (i = 0; i < N; i++)
          P[i][0] = T[i];
  //bottom up dynamic programing
      for (j = 1; 1 << j < N; j++)
         for (i = 0; i < N; i++)
             if (P[i][j - 1] != -1)
                 P[i][j] = P[P[i][j - 1]][j - 1];
}

int query(int N, int P[MAXN][LOGMAXN], int T[MAXN], int L[MAXN], int p, int q){
      int tmp, log, i;
    //if p is situated on a higher level than q then we swap them
      if (L[p] < L[q])
      	swap(p,q);
  //we compute the value of [log(L[p)] - can use also LGMAX-1
      for (log = 1; 1 << log <= L[p]; log++);
      log--;
  //we find the ancestor of node p situated on the same level
  //with q using the values in P
      for (i = log; i >= 0; i--)
          if (L[p] - (1 << i) >= L[q])
              p = P[p][i];
      if (p == q)
          return p;
  //we compute LCA(p, q) using the values in P
      for (i = log; i >= 0; i--)
          if (P[p][i] != -1 && P[p][i] != P[q][i])
              p = P[p][i], q = P[q][i];
      return T[p];
}
