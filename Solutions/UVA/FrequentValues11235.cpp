#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class SegmentTree{
  private: vi A,st;
  int n;
  int left (int p){ return p << 1; }
  int right(int p){ return (p << 1) + 1;}

  void build(int p, int L, int R){
    if(L == R){
      st[p] = A[L];
    }else{
      build(left(p),L,(L+R)/2);
      build(right(p),(L+R)/2 + 1, R);
      int p1 = st[left(p)];
      int p2 = st[right(p)];
      st[p] = max(p1,p2);
    }
  }

  int rmq(int p, int L, int R, int i, int j){
    if(i > R || j < L) return -1;
    if(L >= i && R <= j) return st[p];
    
    int p1 = rmq(left(p),L,(L+R)/2,i,j);
    int p2 = rmq(right(p),(L+R)/2+1,R,i,j);
    
    if(p1 == -1) return p2;
    if(p2 == -1) return p1;

    return max(p1,p2);
  }

public: 
  SegmentTree(const vi &_A){
    A = _A; n = (int)A.size();
    st.assign(4*n,0);
    build(1,0,n-1);
  }

  int rmq(int i, int j){ return rmq(1,0,n-1,i,j); }
};

int arr[100005];

int main(){

  int n,q,x;
  while(cin >> n){
    if(n == 0) break;
    cin >> q;
    vi nums(n);
    int count = 1;
    for(int i = 0; i < n; i++){
      cin >> arr[i];
      if(i > 0 and i != n-1){
        if(arr[i] == arr[i-1]){
          count++;
        }else{
          for(int j = i-count; j < i; j++)
            nums[j] = count;
          count = 1;
        }
      }
      if(i == n-1){
        if(arr[i] == arr[i-1]){
          count++;
          for(int j = i-count+1; j <= n-1; j++)
            nums[j] = count;
        }else{
          for(int j = i-count; j < i; j++)
            nums[j] = count;
          nums[n-1] = 1;
        }
      }
    }

    SegmentTree st(nums);
    int i,j;
    while(q--){
      cin >> i >> j;
      i--; j--;
      int p1 = -1,p2 = -1;
      if(arr[i] == arr[j]){
        cout << j-i+1 << endl;
        continue;
      }
      if(i > 0 and arr[i] == arr[i-1]){
        p1 = 0;
        while(arr[i] == arr[i-1]){
          p1++;
          i++;
        }
      }
      if(j < n-1 and arr[j] == arr[j+1]){
        p2 = 0;
        while(arr[j] == arr[j+1]){
          j--;
          p2++;
        }
      }
      int ans = max(p1,p2);
      if(i <= j) ans = max(ans,st.rmq(i,j));
      cout << ans << endl;
    }
  }

  return 0;
}