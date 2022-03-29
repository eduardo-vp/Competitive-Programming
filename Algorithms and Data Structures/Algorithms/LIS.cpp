// Simple O( nlogn ) Longest Increasing Subsequence
// Answer is stored in array b[N]

int LIS(vector<int> &a){
   int sz = 0;
   vector<int> b(a.size() + 1, 0);
   for (int x: a) {
      int j = lower_bound(b.begin(), b.begin() + sz, x) - b.begin();
      // (lower) a < b < c
      // (upper) a <= b <= c
      b[j] = x;
      if(j == sz) sz++;
   }
   return sz;
}
