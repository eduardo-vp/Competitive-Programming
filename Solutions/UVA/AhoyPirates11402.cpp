#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class SegmentTree{
	private: vi st, A;
	vector<char> lazy;
	int n;
	int left (int p){ return p << 1; }
	int right(int p){ return (p << 1) + 1;}

	void build(int p, int L, int R){
		if(L == R)
			st[p] = A[L];
		else{
			build(left(p),L,(L+R)/2);
			build(right(p),(L+R)/2 + 1, R);
			int p1 = st[left(p)], p2 = st[right(p)];
			st[p] = p1+p2;
		}
	}

	void changeState(int p){
		if(lazy[p] == 'I'){
			lazy[p] = 'X';
			return;
		}
		if(lazy[p] == 'E'){
			lazy[p] = 'F';
			return ;
		}
		if(lazy[p] == 'F'){
			lazy[p] = 'E';
			return ;
		}
		if(lazy[p] == 'X'){
			lazy[p] = 'I';
			return;
		}
	}

	int rmq(int p, int L, int R, int i, int j){

		if(lazy[p] != 'X'){
			if(lazy[p] == 'E'){
				st[p] = 0;
			}else if(lazy[p] == 'F'){
				st[p] = (R-L+1);
			}else{
				st[p] = (R-L+1)-st[p];
			}
			//cout << "UPDATE " << "st[" << L << "," << R << "] = " << st[p] << endl;
			if(L != R){
				if(lazy[p] == 'I'){
					changeState(left(p));
					changeState(right(p));
				}else{
					lazy[left(p)] = lazy[p];
					lazy[right(p)] = lazy[p];	
				}
			}
			lazy[p] = 'X';
		}

		if(i > R || j < L) return 0;
		if(L >= i && R <= j) return st[p];

		int p1 = rmq(left(p),L,(L+R)/2,i,j);
		int p2 = rmq(right(p),(L+R)/2+1,R,i,j);
		/*cout << "L = " << L << " R = " << R << " ";
		cout << "p1 = " << p1 << " p2 = " << p2 << endl;
		*/
		return p1+p2;
	}

	void update(int p, int L, int R, int i, int j, char x){
		if(lazy[p] != 'X'){
			if(lazy[p] == 'E'){
				st[p] = 0;
			}else if(lazy[p] == 'F'){
				st[p] = (R-L+1);
			}else{
				st[p] = (R-L+1)-st[p];
			}
			if(L != R){
				if(lazy[p] == 'I'){
					changeState(left(p));
					changeState(right(p));
				}else{
					lazy[left(p)] = lazy[p];
					lazy[right(p)] = lazy[p];	
				}
			}
			lazy[p] = 'X';
		}
		// no overlap
		if(i > R || j < L) return;
		//total overlap
		if(L >= i && R <= j){
			if(x == 'E'){
				st[p] = 0;
			}else if(x == 'F'){
				st[p] = R-L+1;
			}else{
				st[p] = R-L+1 - st[p];
			}
			if(L != R){
				if(x == 'I'){
					changeState(left(p));
					changeState(right(p));
				}else{
					lazy[left(p)] = x;
					lazy[right(p)] = x;	
				}
			}
			return;
		}
		//partial overlap
		update(left(p),L,(L+R)/2,i,j,x);
		update(right(p),(L+R)/2+1,R,i,j,x);
		st[p] = st[left(p)] + st[right(p)];
	}

public: 
	SegmentTree(const vi &_A){
		A = _A; n = (int)A.size();
		st.assign(4*n,0);
		lazy.assign(4*n,'X');
		build(1,0,n-1);
	}

	int rmq(int i, int j){ return rmq(1,0,n-1,i,j); }

	void update(int i, int j, int x){ return update(1,0,n-1,i,j,x); }
};

int main(){

	int tc,x,y;
	cin >> tc;
	for(int count = 0; count < tc; count++){
		printf("Case %d:\n",count+1);
		int m,a,q = 1,len = 0;
		scanf("%d",&m);
		char cad[1024000];
		char aux[1000000];
		while(m--){
			scanf("%d %s",&a,aux);
			while(a--){
				for(int i = 0; i < strlen(aux); i++)
					cad[len++] = aux[i];
			}
		}
		vi A;
		for(int i = 0; i < len; i++)
			A.pb(cad[i]-'0');
		SegmentTree st(A);
		char c;
		scanf("%d\n",&a);
		while(a--){
			scanf("%c %d %d\n",&c,&x,&y);
			if(c != 'S'){
				st.update(x,y,c);
			}else{
			
				printf("Q%d: %d\n",q++,st.rmq(x,y));
				
			}
		}
	}

	return 0;
}