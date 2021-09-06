struct UF{
  int p[N];
  UF(){ REP(i,0,N) p[i] = i; }
  int find(int i){ return (p[i] == i) ? i : (p[i] = find(p[i])); }
  void join(int i, int j){ p[find(i)] = find(j); }
};
