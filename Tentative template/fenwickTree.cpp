#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class FenwickTree{
  private : vi ft;
    int LSO(int b){ return (b & (-b) ); }
  public: 
    FenwickTree(int n){ ft.assign(n+1,0);}
    int rsq(int b){
      int sum = 0; for(;b ; b-= LSO(b)) sum+= ft[b];
      return sum; }
    int rsq(int a, int b){
      return rsq(b) - (a == 1? 0 : rsq(a-1)); }
    //adjusts value of the k-th element by v
    void adjust(int k, int v){
      for(; k < (int)ft.size(); k += LSO(k)) ft[k] += v;
    }
};

int main(){
  int f[] = {2,4,5,5,6,6,6,7,7,8,9};
  FenwickTree ft(10);
  for(int i = 0; i < 11; i++) ft.adjust(f[i],1);
  printf("%d\n",ft.rsq(1,1)); // ft[1] = 0
  printf("%d\n",ft.rsq(1,2)); // ft[2] = 1
  printf("%d\n",ft.rsq(1,6)); // ft[6] + ft[4] = 5+2 = 7
  printf("%d\n",ft.rsq(1,10)); // ft[10] + ft[8] = 1+10 = 11
  printf("%d\n",ft.rsq(3,6)); // rsq(1,6) - rsq(1,2) = 7 - 1 = 6
  ft.adjust(5,2); // update demo
  printf("%d\n",ft.rsq(1,10)); // now 13
}