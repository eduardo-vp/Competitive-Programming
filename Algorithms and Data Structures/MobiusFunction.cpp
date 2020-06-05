
int mu[N];
bool prime[N];

void fill_mu() {
	REP(i,0,N) mu[i] = 1;
	REP(i,0,N) prime[i] = true;
	for(ll p = 2; p < N; ++p){
		if(prime[p]) {
			for(ll k = 2*p; k < N; k += p) prime[k] = false;
			for(ll k = p; k < N; k += p) mu[k] *= -1;
			for(ll k = p*p; k < N; k += p*p) mu[k] = 0;
		}
	}
}
