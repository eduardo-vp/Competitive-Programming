// Works for queries in non-decreasing order and lines with non-decreasing slopes

struct Line{
	ll m,b;
	ll eval(ll x){ return m*x + b; }
	long double intersectX(Line l){ return (long double)(b - l.b) / (l.m - m); }
};

struct LineContainer{
	deque<Line> dq;
	void add(ll k, ll m) {
		Line now = {k,m};
		if(!sz(dq)){
			dq.push_back(now);
			return;
		}
		if(dq.back().m == now.m){
			while(sz(dq) && dq.back().m == now.m){
				now.b = max(now.b, dq.back().b);
				dq.pop_back();
			}
		}else{
			assert(now.m > dq.back().m);
			while(sz(dq) >= 2 && now.intersectX(dq.back()) <= dq.back().intersectX(dq[sz(dq)-2]))
				dq.pop_back();
		}
		dq.push_back(now);
	}
	ll query(ll x) {
		while(sz(dq) >= 2 && dq[0].eval(x) <= dq[1].eval(x)){
			dq.pop_front();
		}
		return dq.front().eval(x);
	}
};
