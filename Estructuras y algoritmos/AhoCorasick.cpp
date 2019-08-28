
#define N 100005
/* Considerar el alfabeto valido en el problema 
   para limpiar los arreglos */

int n;
char pch[N];
int t[N][130],gt[N][130],link[N],p[N];
vector<int> leaf[N];

int add_string(string &s, int id){
	int u = 0;
	for(char c : s){
		if(t[u][c] == -1){ 
			t[u][c] = n++;
			p[n-1] = u;
		}
		u = t[u][c];
		pch[u] = c;
	}
	leaf[u].pb(id);
	return u;
}

int go(int v, char c);

int get_link(int v){
	if(link[v] == -1){
		if(!v or !p[v]) link[v] = 0;
		else link[v] = go(get_link(p[v]),pch[v]);
	}
	return link[v];
}

int go(int v, char c){
	if(gt[v][c] == -1){
		if(t[v][c] != -1) gt[v][c] = t[v][c];
		else gt[v][c] = (v == 0) ? 0 : go(get_link(v),c);
	}
	return gt[v][c];
}

int main(){

	n = 1;
	fill(t,-1);
	fill(gt,-1);
	fill(link,-1);

	return 0;
}

