// dile a la jardinera que traigo flores
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define pb push_back
#define ff  first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) ll(x.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
 
#define N 100005
#define mod 1000000007
#define N1 105
#define sqr(x) (x)*(x)
#define INF 2000000000000000000
 
using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii > tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> set_t;
 
#define trace(...) f(#__VA_ARGS__, __VA_ARGS__)
 
template<typename t> void f(const char* x, t&& val1){
  cout<<x<< " : "<<val1<<endl;
}
template<typename t1, typename... t2> void f(const char* x, t1&& val1, t2&&... val2){
  const char* xd=strchr(x+1, ',');
  cout.write(x, xd-x)<<" : "<<val1<<" | ";
  f(xd+1, val2...);
}
struct EB{
    ll n;
    vi match, vis, tmp;
    set<ii> used;
    inline void join(ll a, ll b) {
        match[a]=b, match[b]=a;
    }
    inline bool dfs(ll k, vector<vi> &com, vi &blossom){
        vis[k]=0;
        FER(i,0,n) if(com[k][i]){
            if(vis[i]==-1){
                vis[i]=1;
                if(match[i]==-1 || dfs(match[i], com, blossom)) {join(k, i); return true;}
            }
            if(vis[i]==0 || sz(blossom)){
                blossom.pb(i), blossom.pb(k);
                if(k==blossom[0]) {match[k]=-1; return true;}
                return false;
            }
        }
        return false;
    }
    inline bool augment(vector<vi> &com){
        FER(m,0,n) if(match[m]==-1){
            vi blossom;
            vis=vi(n, -1);
            if(!dfs(m, com, blossom)) continue;
            if(sz(blossom)==0) return true;
            ll base=blossom[0], s=sz(blossom);
            vector<vi> newcom=com;
            FER(i,1,s-1) FER(j,0,n) newcom[base][j]=newcom[j][base]|=com[blossom[i]][j];
            FER(i,1,s-1) FER(j,0,n) newcom[blossom[i]][j]=newcom[j][blossom[i]]=0;
            newcom[base][base]=0;
            if(!augment(newcom)) return false;
            ll k=match[base];
            if(k!=-1) FER(i,0,s) if(com[blossom[i]][k]){
                join(blossom[i], k);
                if(i&1) for(ll j=i+1; j<s; j+=2) join(blossom[j], blossom[j+1]);
                else for(ll j=0; j<i; j+=2) join(blossom[j], blossom[j+1]);
                break;
            }
            return true;
        }
        return false;
    }
    inline ll edmonds(vector<vi> & com){
        ll res=0;
        match=vi(n, -1);
        while(augment(com)) res++;
        return res;
    }
    inline void preprocess(vector<vi> &com){
        tmp.clear();
        tmp.assign(n, 0);
        FER(i,0,n) com.pb(tmp);
        used.clear();
        match.clear();
        vis.clear();
    }
    inline void add(ll a, ll b, vector<vi> &com){
        if(a>b) swap(a, b);
        if(used.count({a, b})) return;
        used.insert({a, b});
        com[a][b]=com[b][a]=1;
        
    }
}eb;
vector<vi> com;
string s;
int main(){
    fastio;
    ll t; cin>>t;
    while(t--){
        ll n, m, lady; cin>>n>>m;
        eb.n=(n<<1)+m;
        com.clear();
        eb.preprocess(com);
        FER(i,0,n){
            cin>>s;
            eb.add(i<<1, i<<1|1, com);
            FER(j,0,m) {
                if(s[j]-'0'==1) {
                    lady=j+(n<<1);
                    eb.add(i<<1, lady, com);
                    eb.add(i<<1|1, lady, com);
                }
            }
        }
        ll froz=eb.edmonds(com);
        froz-=n;
        froz=max(0LL, froz);
        cout<<froz<<endl;
    }    
    return 0;
}