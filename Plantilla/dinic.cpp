#include <bits/stdc++.h>
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define fill(x,v) memset(x,v,sizeof(x))
#define FOR(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const int maxnode=20000+5;
const int maxedge=1000000+5;
const int oo=1000000000;

int node,src,dest,nedge;
int head[maxnode],point[maxedge],nxt[maxedge],flow[maxedge],capa[maxedge];
int dist[maxnode],Q[maxnode],work[maxnode];
//inicializa el network, con _node igual a numero de nodos, _src como fuente y como _dest como s
void init(int _node,int _src,int _dest) {
    node=_node; src=_src; dest=_dest;
    FOR(i,0,node) head[i]=-1;
    nedge=0;
}
//anhade la arista de u a v con capacidad c1 y la arista de v a u con capacidad c2
void add(int u,int v,int c1,int c2){
    point[nedge]=v,capa[nedge]=c1,flow[nedge]=0,nxt[nedge]=head[u],head[u]=nedge;
    nedge++;
    point[nedge]=u,capa[nedge]=c2,flow[nedge]=0,nxt[nedge]=head[v],head[v]=nedge;
    nedge++;
}
//bfs de dinic
bool dinic_bfs() {
    fill(dist,-1);
    dist[src]=0;
    int sizeQ=0;
    Q[sizeQ++]=src;
    FOR(cl,0,sizeQ){
        for (int k=Q[cl],i=head[k];i>=0;i=nxt[i]){
            if (flow[i]<capa[i] && dist[point[i]]<0){
                dist[point[i]]=dist[k]+1;
                Q[sizeQ++]=point[i];
            }
        }
    }
    return dist[dest]>=0;
}
//dfs de dinic
int dinic_dfs(int x,int exp) {
    if (x==dest) return exp;
    for (int i=work[x];i>=0;i=nxt[i]){
        int v=point[i],tmp;
        if (flow[i]<capa[i] && dist[v]==dist[x]+1 &&
            (tmp=dinic_dfs(v,min(exp,capa[i]-flow[i])))>0) {
            flow[i]+=tmp;
            flow[i^1]-=tmp;
            return tmp;
        }
    }
    return 0;
}
//flujo
int dinic_flow() {
    int result=0;
    while (dinic_bfs()) {
        FOR(i,0,node) work[i]=head[i];
        while (1) {
            int delta=dinic_dfs(src,oo);
            if (delta==0) break;
            result+=delta;
        }
    }
    return result;
}

int main(){
    /*
    init(6,0,5);
    add(0,1,3,0);
    add(0,4,2,0);
    add(1,3,3,0);
    add(1,2,2,0);
    add(2,5,2,0);
    add(3,5,3,0);
    add(4,2,2,0);
    */

    init(3,0,2);
    add(0,1,3,0);
    add(1,2,2,0);

    cout << dinic_flow() << endl;

    return 0;
}
