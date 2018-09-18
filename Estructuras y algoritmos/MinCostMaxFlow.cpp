#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for (int i=(s),__ee=(e);i<__ee;++i)
#define all(x) begin(x),end(x)
#define clr(x,y) memset(x,y,sizeof x)
#define REP(i,s,f) for (int i = s; i < f; i++)
#define pb push_back
#define sz(v) ((int)v.size())
typedef long long ll;
typedef long double ld;

int n, a, b;
double p[3222], u[3222], eps=1e-7;

const int MAXN = 3010;
struct edge { int dest, cap; double cost; int rev; };
vector<edge> adj[MAXN];
double dis[MAXN], cost;
int source, target, iter, cap;
edge* pre[MAXN];

void addedge(int x, int y, int cap, double cost) {
  adj[x].push_back(edge {y, cap, cost, (int)adj[y].size()});
  adj[y].push_back(edge {x, 0, -cost, (int)adj[x].size() - 1});
}

bool spfa() { // optimization: use dijkstra here and do Johnson reweighting before
	fill(dis, dis + MAXN, 1e12);
  queue<int> q;
  pre[source] = pre[target] = 0;
  dis[source] = 0;
  q.emplace(source);
  while (!q.empty()) {
    int x = q.front();
		double d = dis[x];
    q.pop();
    for (auto& e : adj[x]) {
      int y = e.dest;
			double w = d + e.cost;
      if (e.cap < cap || dis[y] < w + eps) continue;
      dis[y] = w;
      pre[y] = &e;
      q.push(y);  // optimization: only push if not in queue yet
    }
  }
  edge* e = pre[target];
  if (!e || dis[target] > -eps) return 0;  // to minimize (cost, -flow): return also if dis[target] > 0
  while (e) {
    edge& rev = adj[e->dest][e->rev];
    e->cap -= cap;
    rev.cap += cap;
    cost += cap * e->cost;
    e = pre[rev.dest];
  }
  return 1;
}

double mincost(int S, int T) {
  cap = 1, source = S, target = T, cost = 0;
	while(spfa()) {}
  return cost;
}

void show(vector<int>& vec){
	if (sz(vec)) cout << vec[0];
	REP(i,1,sz(vec)) cout << " " << vec[i];
	cout << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> a >> b;
	for (int i = 0; i < n; ++i) cin >> p[i];
	for (int i = 0; i < n; ++i) cin >> u[i];
	int S = n + 1, T = n + 2, P = n + 3, U = n + 4;
	addedge(S, P, a, 0);
	addedge(S, U, b, 0);
	for (int i = 0; i < n; ++i) {
		addedge(P, i, 1, -p[i]);
		addedge(U, i, 1, -u[i]);
		addedge(i, T, 1, 0);
	}
	cout << setprecision(0) << fixed << -mincost(S, T) << endl;
	vector<int> pr;
	vector<int> sp;
	REP(i,0,sz(adj[P])) if (adj[P][i].cap == 0) pr.pb(i);
	REP(i,0,sz(adj[U])) if (adj[U][i].cap == 0) sp.pb(i);
	sort(all(pr));
	sort(all(sp));
	show(pr);
	show(sp);
}
