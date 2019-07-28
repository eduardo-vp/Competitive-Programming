
const ll is_query=-(1LL<<62); // special value for query
struct Line {
	ll m,b;
	mutable multiset<Line>::iterator it,end;
	const Line* succ(multiset<Line>::iterator it) const {
		return (++it==end? NULL : &*it);}
	bool operator<(const Line& rhs) const {
		if(rhs.b!=is_query)return m<rhs.m;
		const Line *s=succ(it);
		if(!s)return 0;
		return (long double)(b-s->b)+1e-9<(long double)((s->m-m)*rhs.m);
	}
};
struct HullDynamic : public multiset<Line> { // for maximum
	bool bad(iterator y){
		iterator z=next(y);
		if(y==begin()){
			if(z==end())return false;
			return y->m==z->m&&y->b<=z->b;
		}
		iterator x=prev(y);
		if(z==end())return y->m==x->m&&y->b<=x->b;
		return (long double)(x->b-y->b)*(z->m-y->m)+1e-9>=(long double)(y->b-z->b)*(y->m-x->m);
	}
	iterator next(iterator y){return ++y;}
	iterator prev(iterator y){return --y;}
	void add(ll m, ll b){
		iterator y=insert((Line){m,b});
		y->it=y;y->end=end();
		if(bad(y)){erase(y);return;}
		while(next(y)!=end()&&bad(next(y)))erase(next(y));
		while(y!=begin()&&bad(prev(y)))erase(prev(y));
	}
	ll eval(ll x){
		Line l=*lower_bound((Line){x,is_query});
		return l.m*x+l.b;
	}
};
