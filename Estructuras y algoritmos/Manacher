#include <bits/stdc++.h>
using namespace std;
// O(n) Manacher's algorithm for finding all palindromes
int n;
char s[200200];
char aux[100100];
int p[200200];

int main(){
   int n;
   scanf("%s", aux);
   n = strlen(aux);
   s[0] = '^';
   s[1] = '#';
   for(int i = 0; i < n; ++i){
      s[2*i+2] = aux[i];
      s[2*i+3] = '#';
   }
   s[2*n+2] = '\0';
   int c = 0, r = 0;
   for(int i = 0; i < 2*n+2; ++i){
      if (i > r) p[i] = 0;
      else p[i] = min(r-i, p[2*c-i]);
      while (s[i+p[i]+1] == s[i-p[i]-1]) p[i]++;
      if (i + p[i] > r){
         c = i;
         r = i + p[i];
      }
   }

   printf("%s\n", s);
   for(int i = 0; i < 2*n+2; ++i){
      printf("%d", p[i]);
   }
   printf("\n");
   printf("%d\n",sum);
   return 0;
}
