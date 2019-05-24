#include <bits/stdc++.h>
#define MAXN 1000050
using namespace std;

string s;
int n,a[MAXN],c[MAXN],head[MAXN],a1[MAXN],c1[MAXN];

inline int f(int x){
	if(x < 0) x += n;
	if(x >= n) x -= n;
	return x;
}

void initSA(){
	// initialize a,c,head
	int cnt[300],clet[300],cant,cc = 0;
	memset(cnt,0,sizeof(cnt));
	for(char l : s) cnt[l]++;
	clet['$'] = cc++;
	head['$'] = 0, head['a'] = 1;
	for(char l = 'a'; l <= 'z'; ++l){ 
		if(cnt[l]) clet[l] = cc++;
		if(l!='z') head[l+1] = head[l] + cnt[l];
	}
	for(int i = 0; i < n; ++i){
		c[i] = clet[s[i]];
		a[head[s[i]]++] = i;
	}
	cant = 1,cc = 0;
	head[0] = cc++;
	for(char l = 'a'; l <= 'z'; ++l)
		if(cnt[l]) head[cc++] = cant, cant += cnt[l];
}

void buildSA(){
	n = s.size();
	initSA();
	// build SA
	int cc;
	for(int L = 1; L < n; L <<= 1){
		for(int i = 0; i < n; ++i){
			int j = f(a[i]-L);
			a1[head[c[j]]++] = j;
		}
		cc = 0;
		for(int i = 0; i < n; ++i){
			if(!i or c[a1[i]] != c[a1[i-1]] or c[f(a1[i]+L)] != c[f(a1[i-1]+L)]){
				head[cc] = i;
				c1[a1[i]] = cc++;
			}else c1[a1[i]] = c1[a1[i-1]];
		}
		for(int i = 0; i < n; ++i) a[i] = a1[i], c[i] = c1[i];
	}
}

int main(){

	cin >> s;
	s += '$';
	buildSA();
	for(int i = 0; i < n; ++i)
		cout << a[i] << " "; cout << endl;
	return 0;
}
