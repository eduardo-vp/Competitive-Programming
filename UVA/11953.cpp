#include <bits/stdc++.h>

#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))

using namespace std;

int n;
string grid[105];
bool survived;

void flood(int x, int y){
	if(x < 0 or x >= n or y < 0 or y >= n) return;
	if(grid[x][y] == '.') return;
	if(grid[x][y] == 'x') survived = true;
	grid[x][y] = '.';
	flood(x,y+1);
	flood(x,y-1);
	flood(x+1,y);
	flood(x-1,y);
}

int main(){

	int t;
	cin >> t;
	for(int tc = 0; tc < t; tc++){
		cin >> n;
		for(int i = 0; i < n; i++)
			cin >> grid[i];
		int ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++){
				if(grid[i][j] != '.'){
					survived = false;
					flood(i,j);
					if(survived) ans++;
				}
			}
		printf("Case %d: %d\n",tc+1,ans);
	}	

	return 0;
}