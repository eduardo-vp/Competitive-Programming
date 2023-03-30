
struct Polygon {
	int n;
  vector<Point> p;
	Polygon() {}
	Polygon(vector<Point> p): p(p), n(p.size()) {}

  // will make clockwise
  void normalize() { // (call before haslog, remove collinear first)
		if (p[2].left(p[0], p[1])) reverse(p.begin(), p.end());
		int pi = min_element(p.begin(), p.end()) - p.begin();
		vector<Point> s(n);
		for (int i = 0; i < n; ++i) {
      s[i] = p[(pi + i) % n];
    }
    p.swap(s);
	}

  bool haslog(Point q) { // O(log(n)) only CONVEX. Call normalize first
		if(q.left(p[0], p[1]) || q.left(p.back(), p[0])) return false;
    // f(a) = false ie point is not to the left of line (p[a] - p[0])
		int a = 1, b = p.size() - 1;  // returns true if point on boundary
		while (b - a > 1) {          // (change sign of EPS in left
			int c = (a + b) / 2;       //  to return false in such case)
			if(!q.left(p[0], p[c])) a = c;
			else b = c;
		}
		return !q.left(p[a], p[a + 1]);
	}
};
