// Simple O( nlogn ) Longest Increasing Subsequence
// Answer is stored in array b[N]

int LIS( vi &a ){
   int b[N];
   int sz = 0;
   FER(i,0,a.size()){
      int j = lower_bound( b , b + sz , a[ i ] ) - b;
      // (lower) a < b < c
      // (upper) a <= b <= c
      b[ j ] = a[ i ];
      if( j == sz ) sz++;
   }
   return sz;
}
