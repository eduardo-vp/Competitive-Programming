/*
https://codeforces.com/blog/entry/74148?#comment-586706
I highly dissuade hashing (multi)sets modulo a prime. Instead: assign random 64bit integer for each element, 
and use xor/sum of all elements as hash of the whole set (xor if we are guaranteed there are no repetitions, 
or we do want repetitions to cancel out, sum if we're hashing a multiset). To get those values of each element
I use following function:

ull mix(ull o){
    o+=0x9e3779b97f4a7c15;
    o=(o^(o>>30))*0xbf58476d1ce4e5b9;
    o=(o^(o>>27))*0x94d049bb133111eb;
    return o^(o>>31);
    //Those constants supposedly are chosen to give this function better pseudo-random properties, 
    but on any on-site contest, when one can't have team reference document/doesn't want to waste time
    searching it for implementation typing arbitrary large odd numbers by hand should be good enough
}

And value used for x is mix(x), or in case of rounds with hacking mix(x ^ salt), where salt is value
returned by chrono::steady_clock::now().time_since_epoch().count() at the beginning of runtime. This
is way faster than anything using modulo, uses all 2^64 possible hash values, so avoids any birthday
paradox issues, also avoids any overflows/issues with and requires way less code than using more than one modulo.

Moreover this technique can be used for hashing other objects than sets, e.g. sequences, which can be represented
as set of pairs (i,ai), the only difference is that now we need random value for each pair, but this can be easily
done e.g. by

ull hash(pii a) {return mix(a.first ^ mix(a.second));}

And finally: using well-known modulos is not an issue, as long as you use random number as base 
(guaranteed by Schwartz–Zippel lemma).
*/

// to use in unordered_set or unordered_map to hash pair<int,int>
struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return ((long long)x.first)^(((long long)x.second)<<32);
  }
};

unordered_set<ii,HASH> x;
unordered_map<ii,int,HASH> y;

// Another way to hash structs
// Hashes is an struct with attributes a,b,c each with an attribute value
namespace std{
  template<>
  struct hash<Hashes>{
    size_t operator()(Hashes const &k)const{
      return k.a.value^k.b.value^k.c.value;
    }
  };
}
// Then declare unordered_maps as unordered_map<Hashes,[type]> h;



// Gracias el vasito
struct Hash {
	int P=1777771,MOD[2],PI[2];
	vector<int> h[2],pi[2];
	Hash(string& s){
		MOD[0]=999727999;MOD[1]=1070777777;
		PI[0]=325255434;PI[1]=10018302;
		REP(k,0,2)h[k].resize(s.size()+1),pi[k].resize(s.size()+1);
		REP(k,0,2){
			h[k][0]=0;pi[k][0]=1;
			ll p=1;
			REP(i,1,s.size()+1){
				h[k][i]=(h[k][i-1]+p*s[i-1])%MOD[k];
				pi[k][i]=(1LL*pi[k][i-1]*PI[k])%MOD[k];
				p=(p*P)%MOD[k];
			}
		}
	}
	ll get(int s, int e){
		ll h0=(h[0][e]-h[0][s]+MOD[0])%MOD[0];
		h0=(1LL*h0*pi[0][s])%MOD[0];
		ll h1=(h[1][e]-h[1][s]+MOD[1])%MOD[1];
		h1=(1LL*h1*pi[1][s])%MOD[1];
		return (h0<<32)|h1;
	}
};
