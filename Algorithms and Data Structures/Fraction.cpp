
// careful with overflow 
struct Frac{
	int p,q;
	Frac(int p, int q) : p(p), q(q){
		int g = __gcd(p,q);
		if(g){
			 p /= g;
			 q /= g;
		}
		if(q < 0){
			p *= -1;
			q *= -1;
		}
		if(p == 0){
			q = 1;
		}
	}
	Frac operator + (Frac f){
		return Frac( p*f.q + f.p*q, q*f.q );
	}
	Frac operator - (Frac f){
		return Frac( p*f.q - f.p*q, q*f.q );
	}
	Frac operator * (Frac f){
		return Frac( p*f.p, q*f.q );
	}
	Frac operator / (Frac f){
		return Frac( p*f.q, q*f.p );
	}
	Frac operator + (int f){
		return *this + Frac(f,1);
	}
	Frac operator - (int f){
		return *this - Frac(f,1);
	}
	Frac operator * (int f){
		return Frac( p*f, q );
	}
	Frac operator / (int f){
		return Frac( p, q*f );
	}
	bool operator == (const Frac &f) const{
		return p == f.p && q == f.q;
	}
};
