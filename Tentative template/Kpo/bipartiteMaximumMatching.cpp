#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define INF 1000000000

vector<vector<int> > adj;
vector<int> U;
vector<int> V;
vector<int> _pair;
vector<int> dist;

bool BFS(){
	queue<int> q;
	for(int i=0;i<U.size();i++){
		int u = U[i];
		if(_pair[u] == 0){
			dist[u] = 0;
			q.push(u);
		}else dist[u] = INF;
	}
	dist[0] = INF;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		if(dist[u] < dist[0]){
			for(int i=0;i<adj[u].size();i++){
				int v = adj[u][i];
				if(dist[_pair[v]] == INF){
					dist[_pair[v]] = dist[u]+1;
					q.push(_pair[v]);
				}
			}
		}
	}
	return dist[0] != INF;
}
bool DFS(int u){
	if(u!=0){
		for(int i=0;i<adj[u].size();i++){
			int v = adj[u][i];
			if(dist[_pair[v]] == dist[u]+1){
				if(DFS(_pair[v])){
					_pair[v] = u;
					_pair[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int hopcroft_karp(){
	int matching = 0;
	for(int i=0;i<U.size();i++) _pair[U[i]] = 0;
	for(int i=0;i<V.size();i++) _pair[V[i]] = 0;
	while(BFS()){
		for(int i=0;i<U.size();i++){
			int u = U[i];
			if(_pair[u]==0){
				if(DFS(u)) matching++;
			}
		}
	}
	return matching;
}

int main() {
	int t;
	cin>>t;
	for(int cas=1;cas<=t;cas++){
		int r,c,num;
		cin>>r>>c;
		U.clear();
		V.clear();
		_pair.clear();
		dist.clear();
		adj.clear();
		for(int i=1;i<=r;i++) U.push_back(i);
		for(int i=1;i<=c;i++) V.push_back(i+r);
		adj.resize(r+c+1);
		_pair.resize(r+c+1);
		dist.resize(r+c+1);
		
		for(int i=1;i<=r;i++){
			for(int j=1;j<=c;j++){
				cin>>num;
				if(num == 1){
					adj[i].push_back(r+j);
					adj[r+j].push_back(i);
				}
			}
		}
		cout<<"Case "<<cas<<": a maximum of "<<hopcroft_karp();
		cout<<" nuts and bolts can be fitted together"<<endl;
	}
	return 0;
}