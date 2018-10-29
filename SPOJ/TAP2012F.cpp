// dile a la jardinera que traigo flores
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define all(v) (v).begin(),(v).end()
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define IFR(i,a,b) for(int i = int(a); i >= int(b); --i)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define N 1024
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;

int nums[10];
int vist[N];
stack<int> st;
map<iii,int> mapa;
map<int,iii> getPair;
vector<string> cads;
vector<int> adj[N];

void dfs(int u){
	vist[u] = 1;
	for(int v : adj[u]){
		if(!vist[v])
			dfs(v);
	}
	st.push(u);
}

int main(){

	fastio;
	int n;
	string cad;
	while(cin >> n){
		if(n == -1) break;
		cads.clear(); mapa.clear(); getPair.clear();
		int cont = 0;
		FER(i,0,n-1){
			cin >> cad;
			cads.pb(cad);
			int a = i+2;
			fill(nums,0);
			for(char c : cad){
				int b = c - '0';
				int z = nums[b];
				nums[b]++;
				iii p = {{min(a,b),max(a,b)}, z};
				if(!mapa.count(p)){
					mapa[p] = cont;
					getPair[cont] = p;
					cont++;
				}
			}
		}
		FER(i,0,cont) adj[i].clear();
		
		FER(i,0,n-1){
			string l = cads[i];
			int a = i+2;
			fill(nums,0);
			vector<iii> tuplas;
			FER(j,0,sz(l)){
				int b = l[j]-'0';
				int z = nums[b];
				nums[b]++;
				iii p = {{min(a,b),max(a,b)},z};
				tuplas.pb(p);
			}
			FER(j,0,sz(tuplas)-1)
				adj[mapa[tuplas[j]]].pb(mapa[tuplas[j+1]]);
		}
		
		fill(vist,0);
		FER(i,0,cont){
			if(!vist[i])
				dfs(i);
		}

		while(!st.empty()){
			int t = st.top();
			st.pop();
			iii p = getPair[t];
			if(p.ff.ff == 1) cout << p.ff.ss;
		}
		cout << endl;
	}

	return 0;
}