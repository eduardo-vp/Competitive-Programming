// Iterative, fast, non-conmutative segment tree.
typedef int T;
const int MAX = 1e6;

// Identity element of the operation
const T OpId = 0;
// Associative internal operation
T Op(T& val1, T& val2){
    return val1 + val2;
}

// The user should fill t[n, 2*n)
T t[2*MAX]; 
int n;   

void build(){
    for( int i = n-1 ; i > 0 ; i-- ) t[i] = Op(t[i<<1], t[i<<1|1]);
}

void modify( int p , T val ){
    for( t[p+=n] = val ; p >>= 1 ; ) t[p] = Op(t[p<<1], t[p<<1|1]);
}

T get( int l , int r ){ //[l,r)
    T ansl, ansr;
    ansl = ansr = OpId; //Initialize operation at Identity
    for( l += n, r += n ; l < r ; l >>= 1, r >>= 1 ){
	    if(l&1) ansl = Op(ansl, t[l++]);
	    if(r&1) ansr = Op(t[--r], ansr);
    }
    return Op(ansl, ansr);
}


int main(){
	// Read into t[n,2*n)
    build();
    // Answer queries
}
