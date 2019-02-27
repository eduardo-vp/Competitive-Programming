// Aimi >> Konomi Suzuki >> Yui >>  Ikimono Gakari >> Garninelia >> Kalafina... dude?
 
// .... Sempre Amei Você ...
 
// Sempre amei você
// Mesmo de longe sem te ter
// Você me deu forças para viver
// E ser quem eu queria ser
// 
// 
// Você nunca verá uma menina como ela
// Mais linda em sentimentos que romance de novela
// Bela, ingênua, tipo como cinderela
// Sorte é do homem que estiver ao lado dela
// Guerreira, não compare com as demais
// Lutou muito para cumprir a exigência de seus pais
// Sua força vai além do que cê pensa ser capaz
// Essa menina não desiste daquilo que vai atrás, mas
// Eu fui tão cego pra não ver
// Que apenas ao meu lado ela queria viver
// Enquanto que por outra pessoa eu quis correr
// Ela não desistiu de mim mesmo eu a fazendo sofrer
// Que idiota, como eu não pude perceber?
// Que a menina que me amava estava sempre ali pra ver
// Eu sei que esse sentimento eu não mereço ter
// Mas desta vez eu vou tentar com meus erros aprender
//
// 
// Sempre amei você
// Mesmo de longe sem te ter
// Você me deu forças para viver
// E ser quem eu queria ser
// 
// 
// Ela sempre esteve lá, pra me ajudar
// Quando eu caí, me fez levantar
// Lutei tanto por meu sonho que sempre quis alcançar
// Que acabei ficando cego sem poder enxergar
// Eu nem consegui notar
// Que bem na minha frente era quem deveria amar
// Sempre achei que estava certo e que não podia errar
// Mas só mesmo quando perde pra então valorizar
// E eu perdi, e finalmente entendi
// Que quem eu procurava estava sempre ali
// Levou muito tempo pra ficha cair
// Como eu fui tapado, eu tenho que admitir
// Essa menina conseguiu me surpreender
// Seu olhar estava sempre além do que eu podia ver
// Eu tive que a perder, só pra perceber
// Que ao lado dela é onde eu quero viver
// 
// 
// Sempre amei você
// Mesmo de longe sem te ter
// Você me deu forças para viver
// E ser quem eu queria ser
// 
// 
// Eu tive que a perder
// Pra que pudesse perceber
// Que ao lado dela
// É onde eu quero viver
// Sim, um dia pode ser o fim
// Pode ser tarde demais e tudo acabar assim
// Mas pra ela eu vou dizer
// Não volto com minha palavra
// Com você quero viver
// 
// 
// Sempre amei você
// Mesmo de longe sem te ter
// Você me deu forças para viver
// E ser quem eu queria ser 
 
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
 
#define N 14000015
#define sqr(x) (x)*(x)
#define INF 5000000000
#define mod 1000000007
#define bas 31
#define pi acos(-1) 

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

struct Edge{
    ll a, b, l, r;
    Edge(){}
    Edge(ll a, ll b, ll l, ll r): a(a), b(b), l(l), r(r){}
};

vi adj[1<<19];
ll vis[1<<19], col[1<<19], deg[1<<19], cnt[1<<19], ans[1<<19];

inline void dfs(ll u, ll val){
    vis[u]++, col[u]=val;
    for(auto xd: adj[u]) if(!vis[xd]) dfs(xd, val);
}

inline void Add(ll a, ll b){
    adj[a].pb(b);
    adj[b].pb(a);
    return;
}
inline void solve(ll l, ll r, vector<Edge> &v, ll comp, ll add){
    if(cnt[l]==cnt[r]) return;
    if(!sz(v)){
        FER(i,l,r) ans[i]=comp+add;
        return;
    }
    FER(i,0,comp) adj[i].clear(), vis[i]=0;
    vector<Edge> v1;
    for(auto xd: v){
        if(xd.a==xd.b) continue;
        if(xd.l<=l && r<=xd.r) Add(xd.a, xd.b);
        else if(l<xd.r && xd.l<r) v1.pb(xd);
    }
    ll n=0, new_n;
    FER(i,0,comp) if(!vis[i]) deg[n]=0, dfs(i, n++);
    for(auto &xd: v1){
        xd.a=col[xd.a], xd.b=col[xd.b];
        if(xd.a!=xd.b) deg[xd.a]++, deg[xd.b]++;
    }
    new_n=n, n=0;
    FER(i,0,new_n){
        vis[i]=n;
        n+=(deg[i]>0);
        add+=!deg[i];
    }
    for(auto &xd: v1) xd.a=vis[xd.a], xd.b=vis[xd.b];
    ll mid=(l+r)>>1;
    solve(l, mid, v1, n, add);
    solve(mid, r, v1, n, add);
}

int main(){
    // fastio;
    #define NAME "connect"
    assert(freopen(NAME ".in", "r", stdin));
    assert(freopen(NAME ".out", "w", stdout));
    ll n, k; cin>>n>>k;
    char s;
    ll a, b;
    map<ii, ll> m;
    vector<Edge> v;
    FER(i,0,k){
        cin>>s;
        if(s=='+' || s=='-'){
            cin>>a>>b; a--; b--;
            if(a==b) {k--, i--; continue;}
            if(a>b) swap(a, b);
            if(s=='+') m[{a, b}]=i;
            else{
                ll &j=m[{a, b}];
                v.pb({a, b, j, i});
                j=-1;
            }
        }
        else cnt[i+1]++;
        cnt[i+1]+=cnt[i];
    }
    for(auto xd: m) if(xd.ss!=-1) v.pb({xd.ff.ff, xd.ff.ss, xd.ss, k});
    solve(0, k, v, n, 0);
    FER(i,0,k) if(cnt[i+1]!=cnt[i]) cout<<ans[i]<<endl;
    return 0;
}
