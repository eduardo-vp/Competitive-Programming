#include <bits/stdc++.h>

#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;

char grid[25][25];

int m,n;

int flood(int x, int y, char a, char b){
  //cout << "visiting " << x << " " << y << endl;
  if(x < 0 or x >= m or y < 0 or y >= n or grid[x][y] != b)
    return 0;
  int ans = 1;
  grid[x][y] = a;
  ans += flood(x,(y+1)%n,a,b);
  ans += flood(x, (y+n-1)%n,a,b);
  ans += flood(x-1,y,a,b);
  ans += flood(x+1,y,a,b);
  return ans;
}

void test(){ cout << "Holi" << endl; }

int main(){

  while(cin >> m >> n){
    
    int x,y;
    char c1,c2;
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++){
        cin >> grid[i][j];
        if(i == 0 and j == 0) c1 = grid[i][j];
        else if(grid[i][j] != c1) c2 = grid[i][j];
      }
    
    cin >> x >> y;
    char land = grid[x][y];
    char water = (c1 == land) ? c2 : c1;
    if(land == water) land = water+1;
    flood(x,y,water,land);
    int ans = 0;
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++){
        if(grid[i][j] == land)
          ans = max(ans,flood(i,j,water,land));
      }
    cout << ans << endl;
  }

  return 0;
}