// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf
#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define FER(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define MAXN 1000010
#define MAXLG 25
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

// r is the list of sorted suffixes
// p is the position of i in the sorted list
int n,t;
string s;
int p[MAXN],r[MAXN],h[MAXN];
int rmq[MAXLG][MAXN];
int flog2[MAXN];

void fit_index(int b, int e){
	int lastpk, pk, d;
	lastpk = p[r[b]+t];
	d = b;
	FER(i,b,e){
		if(((pk = p[r[i]+t]) != lastpk) and (b > lastpk or pk >= e)){
				lastpk = pk;
				d = i;
		}
		p[r[i]] = d;
	}
}

void suff_arr(){
	int bc[256];
	FER(i,0,256) bc[i] = 0;
	FER(i,0,n) bc[int(s[i])]++;
	FER(i,1,256) bc[i] += bc[i-1];
	for(int i = n-1; i >= 0; --i) r[--bc[int(s[i])]] = i;
	for(int i = n-1; i >= 0; --i) p[i] = bc[int(s[i])];
	for(t = 1; t < n; t <<= 1){
		for(int i = 0, j = 1; i < n; i = j++){
			while(j < n and p[r[j]] == p[r[i]]) ++j;
			if(j-i > 1){
				sort(r+i,r+j,[&](const int &i, const int &j){
					return p[i+t] < p[j+t];
				});
				fit_index(i,j);
			}
		}
	}
}

void init_lcp(){
	int tam = 0, j;
	FER(i,0,n-1){
		j = r[p[i]-1];
		while(s[i+tam] == s[j+tam]) ++tam;
		h[p[i]-1] = tam;
		if(tam > 0) --tam;
	}
}

void make_lcp(){
	init_lcp();
	FER(i,0,n-1) rmq[0][i] = h[i];
	int lg = 0, pw = 1;
	do{
		FER(i,pw,pw*2) flog2[i] = lg;
		lg++, pw *= 2;
		FER(i,0,n-1){
			if(i+pw/2 < n-1) rmq[lg][i] = min(rmq[lg-1][i],rmq[lg-1][i+pw/2]);
			else rmq[lg][i] = rmq[lg-1][i];
		}
	}while(pw < n);
}

// Lcp in interval [i,j]
int lcp(int i, int j){
	if(i == j) return n - r[i] - 1;
	int lg = flog2[j-i], pw = (1 << lg);
	return min(rmq[lg][i], rmq[lg][j-pw]);
}

int main(){

	cin >> s;
	s += '$';
	n = sz(s);
	suff_arr();
	make_lcp();
	return 0;
}
