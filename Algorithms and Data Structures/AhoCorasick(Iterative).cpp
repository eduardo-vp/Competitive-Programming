
const int N = 1e5+20;
/*Considerar las letras del alfabeto
  Llamar build() antes de usar 
  Para transicionar llamar ahc.go[u][f(ch)] */

inline int f(char ch){
	if(ch >= 'a' && ch <= 'z') return ch - 'a';
	if(ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
	return ch - '0' + 52;
}
 
struct AhoCorasick{
	int cnt;
	char pch[N];
	int t[N][65],go[N][65],link[N],slink[N],p[N];
	int leaf[N];
	AhoCorasick(){
		cnt = 1;
		memset(t,-1,sizeof(t));
		memset(leaf,-1,sizeof(leaf));
	}
	int add_string(string &s, int id){
		int u = 0;
		for(char ch : s){
			int c = f(ch);
			if(t[u][c] == -1){
				p[cnt] = u;
				t[u][c] = cnt++;
			}
			u = t[u][c];
			pch[u] = ch;
		}
		leaf[u] = id;
		return u;
	}
	void build(){
		queue<int> q;
		p[0] = 0;
		q.push(0);
		while(sz(q)){
			int u = q.front(); q.pop();
			int lk = link[u] = (p[u] == 0) ? 0 : go[link[p[u]]][f(pch[u])];
			if(lk == 0) slink[u] = 0;
			else slink[u] = (leaf[lk] >= 0) ? lk : slink[lk];
			for(char ch : alphabet){ // replace accordingly
				int c = f(ch);
				if(t[u][c] > 0){
					q.push(t[u][c]);
					go[u][c] = t[u][c];
				}else{
					go[u][c] = (u == 0) ? 0 : go[link[u]][c];
				}
			}
		}
	}
 
};
