// Interval Set - Gracias MarcosK
// Añade y quita intervalos en O(logn). 
// Ans guarda el tamaño de la unión de los intervalos
// usage:
//		insert(from,to): Insertar intervalo [from,to].
//		remove(from,to): Borrar intervalos en [from,to].
//		contains(from,to): Chekear si [from,to] está en el conjunto.

struct IntervalSet{
	set<ii> st;
	int ans;

	void insert(int from, int to){
		vector<ii> toer;
		auto it = st.upper_bound(ii(to + 1,oo)); // +1 combinar consecutivos
		while(it != st.begin()){
			it --;
			ii x = *it;
			if(x.ss + 1 < from) break; // +1
			toer.pb(x);
		}
		for(auto x: toer){
			st.erase(x);
			from = min(x.ff, from), to = max(x.ss, to);
			ans -= x.ss - x.ff + 1;
		}
		st.insert(ii(from,to));
		ans += to - from + 1;
	}

	void remove(int from, int to){
		vector<ii> toer;
		auto it = st.upper_bound(ii(to + 1,oo)); // +1
		if(it == st.begin()) return;
		while(it != st.begin()){
			it --;
			ii x = *it;
			if(x.ss + 1 < from) break; // +1
			toer.pb(x);
		}
		for(auto x: toer){
			st.erase(x);
			ans -= x.ss - x.ff + 1;
			if(x.ss > to) st.insert(ii(to+1, x.ss)), ans += x.ss - to;
			if(x.ff < from) st.insert(ii(x.ff, from-1)), ans += from - x.ff;
		}
	}

	bool contains(int from, int to){
		auto it = st.upper_bound(ii(right, oo));
		if(it == st.begin()) return false;
		it --;
		ii ivl = *it;
		return (from >= ivl.ff and to <= ivl.ss);
	}
};
