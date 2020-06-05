
// finds the point to shift s to make it its lexicographical smallest cyclic shift
int min_rotation(vl s) {
	int a=0, N=sz(s); 
	s.insert(s.end(),all(s));
	F0R(b,N) F0R(i,N) {
		if (a+i == b || s[a+i] < s[b+i]) {b += max(0, i-1); break;}
		if (s[a+i] > s[b+i]) { a = b; break; }
	}
	return a;
}

// rotates v
vl rot_min(vl v) {
    int x = min_rotation(v);
    rotate(v.begin(),v.begin()+x,v.end());
    return v;
}
