#include <bits/stdc++.h>

#define fr(i,j,k) for(int (i)=(j);(i)<(k);++(i))
#define cl(i) memset(i,0,sizeof(i))

using namespace std;

char in[401][51];
int grid[410][410];
int val[210];
char resp[2000];

int n ,m ;

void paint(int y, int x, int c, int d ){
	if( grid[y][x] != d || y < 0 || y > n || x < 0 || x > m ) return;

	grid[y][x] = c;
	paint( y -1, x , c, d);
	paint( y, x-1 , c, d);
	paint( y +1, x , c, d);
	paint( y , x + 1 , c, d);
}

int main(){
	
	int caso = 1;
	while(scanf("%d%d", &n ,&m ) && (n||m)){
		cl( grid); cl( val); cl( resp);
		fr(i,0,n){
			scanf("%s", in[i]);
		}
		fr(i,0,n){
			fr(j,0,m){
				int aux = ( in[i][j]  >= '0' && in[i][j] <= '9')? (in[i][j] - '0') : (in[i][j] - 'a' + 10);
				int pos = 3;
				// cout << aux << endl;
				while(aux > 0) {
					grid[i][j*4+pos] = (aux & 1);
					aux >>= 1; pos--;
				}
			}
		}
		m *= 4 ;  int ini = 2; bool out = true;
		// fr(i,0,n) { fr(j,0,m) { cout << grid[i][j]; } cout << endl; } cout << endl;
		fr(i,0,n) { fr(j,0,m) { if( i == 0 || i == n-1 ||  j == 0 || j == m-1 ) paint( i, j, 10000, 0); } }
		// fr(i,0,n) { fr(j,0,m) { cout << grid[i][j]; } cout << endl; } cout << endl;
		int base = ini;
		fr(i,0,n){
			fr(j,0,m){
				if( grid[i][j] == 0){ 
					val[ grid[i][j-1] ]++;
					paint( i, j , grid[i][j-1], 0);
				} else if( grid[i][j]  == 1){
					paint( i, j , base++, 1);
				}				
			}
		}
		int num = 0;
		fr(i,ini,base){
			if( val[i] == 0) resp[num++] = 'W';
			if( val[i] == 1) resp[num++] = 'A';
			if( val[i] == 2) resp[num++] = 'K';
			if( val[i] == 3) resp[num++] = 'J';
			if( val[i] == 4) resp[num++] = 'S';
			if( val[i] == 5) resp[num++] = 'D';
		}
		sort( resp, resp + num);
		printf("Case %d: %s\n", caso++, resp);
		
	}
	return 0;
}