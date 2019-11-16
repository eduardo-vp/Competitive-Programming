
// r is the list of sorted suffixes
// p is the position of i in the sorted list
string cad;
int n,r[N],tempr[N],p[N],tempp[N],c[N];

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
		p[i] = cad[i];
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

int main(){

	cin >> cad;
	cad += '$';
	n = sz(cad);

	build();
	REP(i,0,n) cout << r[i] << " ";
	cout << endl;
	REP(i,0,n) cout << p[i] << " ";
	cout << endl;

	return 0;
}
