
// SQ * BL > N
// SQ = Block size
// BL = Number of blocks
const int SQ = 2000, N = 1e5 + 100, BL = 52;

int id[N];

// interval [l,r)
void update(int l, int r, int x){
	if(id[l] == id[r]){
		for(int i = l; i < r; ++i){
			// update position
		}
		return;
	}
	while(l % SQ){
		// update position
		l++;
	}
	while(r % SQ){
		r--;
      		// update position
	}
	for(int i = id[l]; i < id[r]; ++i){
		// update block
	}
}

// interval [l,r)
int query(int l, int r){
	int ans = 0;
	if(id[l] == id[r]){
		for(int i = l; i < r; ++i){
			// query position
		}
		return ans;
	}
	while(l % SQ){
		// query position
		l++;
	}
	while(r % SQ){
		r--;
		// query position
	}
	for(int i = id[l]; i < id[r]; ++i){
		// query block
	}
	return ans;
}

int main(){

	fastio;
	REP(i,N) id[i] = i/SQ;
  
	return 0;
}
