// dile a la jardinera que traigo flores
// corner cases // int vs ll // cin vs scanf // clear structures // statement
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define REP(i,a,b) for(int i = int(a); i < int(b); ++i)
#define trace(x) cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 1000100
#define MAXLG 25
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

// r is the list of sorted suffixes
// p is the position of i in the sorted list
string s;
int n,r[N],tempr[N],p[N],tempp[N],c[N];
int flog2[N],rmq[N][MAXLG],h[N];

void csort(int k){
	int mx = max(n,300);
	REP(i,0,mx) c[i] = 0;
	REP(i,0,n) c[i+k<n ? p[i+k]:0]++;
	REP(i,1,mx) c[i] += c[i-1];
	for(int i = n-1; i >= 0; --i) tempr[--c[r[i]+k<n ? p[r[i]+k]:0]] = r[i];
	REP(i,0,n) r[i] = tempr[i];
}

void build(){
	REP(i,0,n){
		p[i] = s[i];
		r[i] = i;
	}
	for(int k = 1; k < n; k <<= 1){
		csort(k);
		csort(0);
		int x = tempp[r[0]] = 0;
		REP(i,1,n) 
			tempp[r[i]] = (p[r[i]]==p[r[i-1]] && p[r[i]+k]==p[r[i-1]+k]) ? x : ++x;
		REP(i,0,n) p[i] = tempp[i];
		if(x == n-1) break;
	}
}

void init_lcp(){
	int tam = 0, j;
	REP(i,0,n-1){
		j = r[p[i]-1];
		while(s[i+tam] == s[j+tam]) ++tam;
		h[p[i]-1] = tam;
		if(tam > 0) --tam;
	}
}

void make_lcp(){
	init_lcp();
	REP(i,0,n-1) rmq[0][i] = h[i];
	int lg = 0, pw = 1;
	do{
		REP(i,pw,pw*2) flog2[i] = lg;
		lg++, pw *= 2;
		REP(i,0,n-1){
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

	build();
	REP(i,0,n) cout << r[i] << " ";
	cout << endl;
	REP(i,0,n) cout << p[i] << " ";
	cout << endl;

	return 0;
}

