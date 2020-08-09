
int go[N][300];
 
vector<int> prefix_function(string &s){
	int n = sz(s);
	vector<int> p(n);
	p[0] = 0;
	for(int i = 1; i < n; ++i){
		p[i] = p[i-1];
		while(p[i] and s[p[i]] != s[i]) p[i] = p[p[i]-1];
		if(s[p[i]] == s[i]) p[i]++;
	}
	return p;
}
 
void build_automaton(string &s){
	int n = sz(s);
	vector<int> vec = prefix_function(s);
	memset(go,0,sizeof(go));
	for(int i = 0; i < n; ++i) go[i][s[i]] = i+1;
	for(int i = 1; i <= n; ++i)
		for(char j = 'a'; j <= 'z'; ++j){
			if(go[i][j]) continue;
			go[i][j] = go[vec[i-1]][j];
		}
}

void search(string &pat, string &text){
	int cnt = 0;
	vector<int> vec = prefix_function(pat);
	for(char c : text){
		while(cnt and c != pat[cnt]) cnt = vec[cnt-1];
		if(c == pat[cnt]) cnt++;
		if(cnt == sz(pat)){
			// pattern found
			cnt = vec[cnt-1];
		}
	}
}
