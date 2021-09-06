

void kmp(string &cad){
  p[0] = 0;
  for(int i = 1; i < m; ++i){
    p[i] = p[i-1];
    while(p[i] > 0 and cad[p[i]] != cad[i])
      p[i] = p[p[i]-1];
    if(cad[p[i]] == cad[i]) p[i]++;
  }
}
