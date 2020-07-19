
#define REP(i,a,b) for(int i = int(a); i < int(b); ++i)
// const int N = 3;
typedef vector< vector<int> > Mat;
 
void Id(Mat &A){
	REP(i,0,N) REP(j,0,N) A[i][j] = (i == j);
}
 
void Mult(Mat &A, Mat &B, Mat &C){
	REP(i,0,N) REP(j,0,N) C[i][j] = 0;
	REP(i,0,N) REP(j,0,N) REP(k,0,N) C[i][j] += A[i][k] * B[k][j];
}
 
Mat Binpow(Mat x, ll p){
	Mat ans(N,vector<int>(N));
	Mat aux(N,vector<int>(N));
	for(Id(ans); p; p >>= 1){
		if(p&1){
			Mult(ans,x,aux);
			ans = aux;
		}
		Mult(x,x,aux);
		x = aux;
	}
	return ans;
}
