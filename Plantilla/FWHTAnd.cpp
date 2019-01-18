// Kotaro << Minoz << Hayama << Cohr3141592654
 
// Fall...
 
// You know, everybody's been tellin' me what they think about me for the last few months
 
// ... It's too loud
// Maybe it's time I tell 'em what I think about them
// ... Can't hear it coming down the hallway stairs from the parking lot
// ... It's too loud
// ... Three's not a crowd all up in it, slow fire
 
// ... Don't fall on my face
// ... Don't fall on my faith, oh
// ... Don't fall on my fate
// ... Don't fall on my faith, oh
// ... Don't fall on my fate
// ... Don't fall on my
 
// Gotta concentrate, against the clock I race
// Got no time to waste, I'm already late, I got a marathoner's pace
// Went from addict to a workaholic, word to Dr. Dre
// In that first marijuana tape-guess I got a chronic case (yeah)
// And I ain't just blowin' smoke, 'less it's in your momma's face
// I know this time Paul and Dre
// They won't tell me what not to say (nope)
// And though me and my party days
// Have all pretty much parted ways
// You'd swear to God I forgot I'm the guy that made "Not Afraid"
// One last time for Charlamagne
// If my response is late, it's just how long it takes
// To hit my fuckin' radar, I'm so far away
// These rappers are like Hunger Games
// One minute, they're mockin' Jay
// Next minute, they get their style from Migos or they copy Drake
// Maybe I just don't know when to turn around and walk away
// But all the hate, I call it "Walk on Water" gate
// I've had as much as I can tolerate
// I'm sick and tired of waitin', I done lost my patience
// I can take all of you motherfuckers on at once
// You wanted Shady? You got him!
 
// ... Don't fall on my face (yeah)
// ... Don't fall on my faith, oh
// ... Don't fall on my fate (line 'em up!)
// ... Don't fall on my faith, oh (rrr!)
// ... Don't fall on my fate (look)
 
// Somebody tell Budden before I snap, he better fasten it
// Or have his body bag get zipped
// The closest thing he's had to hits is smackin' bitches
// And don't make me have to give it back to Akademiks
// Say this shit is trash again, I'll have you twisted
// Like you had it when you thought you had me slippin' at the telly
// Even when I'm gettin' brain, you'll never catch me with a thot
// Lackin' with it, "he ain't spittin' like this on his last shit"
// Ho, you better go back and listen
// You know me better, thinkin' I'll slow or let up
// Call it trap 'cause it's a total setup
// Hopin' that you rappers fall in that
// Dre said, "Hold your head up!"Kathy Griffin
// Stackin' ammunition, slap the clip in, cock it back on competition
// This is how I shot ahead (pew) Gabby Giffords
// My attack is vicious, Jack the Ripper, back in business
// Tyler create nothin', I see why you called yourself a (faggot), bitch
// It's not just 'cause you lack attention
// It's because you worship D12's balls, you're sack-religious
// If you're gonna critique me
// You better at least be as good or better
// Get Earl the Hooded Sweater
// Whatever his name is to help you put together
// Some words, more than just two letters 
// The fans waited for this moment like that feature
// When I stole the show (ha), sorry if I took forever (haha)
 
// ... Don't fall on my face (yeah)
// ... Don't fall on my faith, oh (I won't)
// ... Don't fall on my fate (line 'em up!)
// ... Don't fall on my faith, oh (ha)
// ... Don't fall on my fate (it's too easy)
 
// Just remember, I was here before you
// And I'll be here after you make your run-in for you
// Detractors, I might have to fuck Pitchfork with a corkscrew
// Just what the doctor ordered
// Revenge is the best medicine
// Increase the dose, from least to most
// And then tell the Grammys to go and fuck themselves
// They suck the blood from all the biggest artists like some leeches
// So they nominate 'em, get 'em there, get a name to MC the show
// Every parasite needs a host (haha)
// Then give Album of the Year to somebody that no one's ever even heard of
// All I know is I wrote every single word of
// Everything I ever murdered
// Time to separate the sheep from goats (yeah)
// And I got no faith in your writers, I don't believe in ghosts
// When rap needed it most, I was that wing and a prayer
// A beacon of hope, put a B-I-R-D in the air
// Somewhere some kid is bumpin' this while he lip-syncs in the mirror
// That's who I'm doin' it for, the rest I don't really even care
// But you would think I'm carryin' a Oxford dictionary in my pocket
// How I'm buryin' these artists
// On a scale of 'turnt' you're 'minus'
// Mine says 'very', yours says 'hardly'
// And what's scary is you probably can compare me to your car 'cause I'm just barely gettin' started (woo)
// And far as Lord Jamar, you better leave me the hell alone
// Or I'll show you an Elvis clone
// Walk up in this house you own, thrust my pelvic bone
// Use your telephone and go fetch me the remote
// Put my feet up and just make myself at home
// I belong here, clown, don't tell me 'bout the culture
// I inspired the Hopsins, the Logics, the Coles, the
// Seans, the K-Dots, the 5'9"s, and oh
// Brought the world 50 Cent, you did squat, piss and moan
// But I'm not gonna fall... bitch!
 
// ... It's too loud
// ... Can't hear it coming down the hallway stairs from the parking lot
// ... It's too loud
// ... Three's not a crowd all up in it
// ... Slow fire
 
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
// #define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
 
#define N 200005
#define mod 1000000007
#define N1 105
#define sqr(x) (x)*(x)
#define INF 2000000000000000000 
#define pi acos(-1);
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

inline ll bp(ll a, ll n){
    if(n==0) return 1;
    if(n&1) return (a*bp(a, n-1))%mod;
    ll x=bp(a, n>>1);
    return (sqr(x)%mod+mod)%mod;
}

// Fast Walsh-Hadamard Transform  for And multiplication
// take note about the matrix associated
// |-1 +1|
// |+1 +0|
// The inverse is not the same as the matrix, so it's necesary
// to have a bool parameter in the convolution

struct FWHTAnd{
    ll n;
    inline void GetInverse(vi &v, ll flag){
        n=1;
        while(n<sz(v)) n<<=1;
        v.resize(n);
        for(ll len=1; (len<<1)<=n; len<<=1){
            for(ll i=0; i<n; i+=(len<<1)){
                FER(j,0,len){
                    ll a=v[i+j], b=v[i+j+len];
                    if(flag){
                        v[i+j]=b;
                        v[i+j+len]=a+b;
                        v[i+len+j]%=mod;
                    }
                    else{
                        v[i+j]=mod-a+b;
                        v[i+j+len]=a;
                        v[i+j]%=mod;
                    }
                }
            }
        }

    }
}fwht;
int main(){
    fastio;
    ll n, top=0, ans=0; cin>>n;
    vi v1, v2;
    FER(i,0,n){
        ll x; cin>>x;
        top=max(top, x);
        v1.pb(x);
    }
    top++;
    v2.resize(top);
    v2[0]=1;
    for(auto xd: v1) v2[xd]=1;
    fwht.GetInverse(v2, 1);
    FER(i,0,fwht.n) v2[i]=bp(v2[i], n);
    fwht.GetInverse(v2, 0);
    FER(i,0,fwht.n) if(v2[i]) ans++;
    cout<<ans<<endl;
    return 0;
}
