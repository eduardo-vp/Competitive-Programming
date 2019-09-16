#include <bits/stdc++.h>
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define sz(x) int(x.size())
using namespace std;

/* Considerar el tamanho del alfabeto */
/* Implementacion para letras minusculas */

#define N 1000100

struct AhoCorasick{

	int cnt;
	char pch[N];
	int t[N][27],gt[N][27],link[N],slink[N],p[N];
	vector<int> leaf[N];

	AhoCorasick(){
		cnt = 1;
		p[0] = 0;
		fill(t,-1);
		fill(gt,-1);
		fill(link,-1);
		fill(slink,-1);
	}

	void add_string(string &s, int id){
		int u = 0;
		for(char ch : s){
			int c = ch - 'a';
			if(t[u][c] == -1){
				t[u][c] = cnt++;
				p[cnt-1] = u;
			}
			u = t[u][c];
			pch[u] = ch;
		}
		leaf[u].pb(id);
	}

	int get_link(int v){
		if(link[v] == -1){
			if(!v or !p[v]) link[v] = 0;
			else link[v] = go(get_link(p[v]),pch[v]);
		}
		return link[v];
	}

	int go(int v, char ch){
		int c = ch - 'a';
		if(gt[v][c] == -1){
			if(t[v][c] != -1) gt[v][c] = t[v][c];
			else gt[v][c] = (v == 0) ? 0 : go(get_link(v),ch);
		}
		return gt[v][c];
	}

	int get_superlink(int u){
		if(slink[u] == -1){
			int lk = get_link(u);
			if(lk == 0) slink[u] = 0;
			else if(sz(leaf[lk])) slink[u] = lk;
			else slink[u] = get_superlink(lk);
		}
		return slink[u];
	}
};
