//dile a la jardinera que traigo flores
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
#define FER(i,a,b) for(ll i = ll(a); i < ll(b); ++i)
#define IFR(i,a,b) for(ll i = ll(a); i >= ll(b); --i)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;
typedef int ll;
typedef pair<ll,ll> ii;
typedef pair<ll,ii> tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define N 100003
#define INF 1000000000
#define mod 1000000007

#define trace(...) f(#__VA_ARGS__,__VA_ARGS__)

template<typename t> void f(const char * x, t&& val1){
  cout << x << " : " << val1 << endl; 
}
template<typename t1, typename... t2> void f(const char * x, t1&& val1, t2&&... val2){
  const char * xd = strchr(x+1,',');
  cout.write(x,xd-x)<<" : " << val1 << " | ";
  f(xd+1,val2...) ;
}
struct CD{
    ll gid, n;
    vi graph[N], adj[N];
    ll tsz[N], p[N], id[N], rt[N];
    ll tsz1[N], p1[N], d1[N];
    inline void add(ll a, ll b){
        graph[a].pb(b);
        graph[b].pb(a);
    }
    inline ll dfs(ll u, ll pp){
        tsz[u]=1;
        for(auto xd: graph[u]) if(xd!=pp && p[xd]==-1) tsz[u]+=dfs(xd, u);
        return tsz[u];
    }
    inline void descompose(ll u, ll pp, ll sb, ll prev){
        for(auto xd: graph[u]) if(xd!=pp && p[xd]==-1 && (tsz[xd]*2) > sb) {descompose(xd, u, sb, prev); return;}
        p[u]=prev; ll pe;
        for(auto xd: graph[u]) if(p[xd]==-1) pe=dfs(xd, -1), descompose(xd, u, tsz[xd], u);
    }
    inline ll dfs1(ll u, ll pp, ll depth){
        p1[u]=pp, d1[u]=depth, tsz1[u]=1;
        for(auto xd: adj[u]) if(xd!=pp) tsz1[u]+=dfs1(xd, u, depth+1);
        return tsz1[u];
    }
    inline void make(ll u){
        ll pe=dfs1(u, -1, 0);
    }
    inline void go(ll u, ll root){
        id[u]=gid++, rt[u]=root;
        ll w=-1, bc=-1;
        for(auto xd: adj[u]) if(xd!=p1[u] && tsz1[xd]>w) w=tsz1[xd], bc=xd;
        if(bc!=-1) go(bc, root);
        for(auto xd: adj[u]) if(xd!=p1[u] && xd!=bc) go(xd, xd);
    }
    inline ll lca(ll a, ll b){
        while(rt[a]!=rt[b]) d1[rt[a]]>d1[rt[b]]? a=p1[rt[a]]: b=p1[rt[b]];
        return d1[a]>d1[b]? b: a;
    } 
    inline void build(ll u){
        FER(i,0,N) p[i]=-1;
        ll ja=dfs(u, -1);
        descompose(u, -1, tsz[u], -2);
        ll nod;
        FER(i,0,n) if(p[i]==-2) {nod=i; break;}
        FER(i,0,n) if(i!=nod) adj[i].pb(p[i]), adj[p[i]].pb(i);
        gid=0;
        make(nod);
        go(nod, nod);
    }
}cd;


int main(){
    fastio;
    ll n; cin>>n;
    cd.n=n;
    FER(i,0,n-1){
        ll a, b; cin>>a>>b; a--; b--;
        cd.add(a, b);
    }
    cd.build(0);
    map<ll, string> m;
    ll pos=0;
    for(char xd='A'; xd<'Z'; xd++) m[pos++]=xd;
    ll flag=0;
    FER(i,0,n) if(cd.d1[i]>26) flag=1;
    if(flag) cout<<"Impossible!"<<"\n";
    else FER(i,0,n) cout<<m[cd.d1[i]]<<"\n";
    return 0;
}