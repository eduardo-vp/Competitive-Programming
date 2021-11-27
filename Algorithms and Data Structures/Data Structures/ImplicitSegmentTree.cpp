
const int MX = 3.7e7;

struct STree {
  long long n;
  int nodes;
  vector<int> left, right;
  vector<long long> t, lazy;
  
  STree(long long n): n(n), nodes(1), left(MX), right(MX), t(MX), lazy(MX) {}
  
  long long comb(long long x, long long y) {
    return x + y;
  }

  void push (int id, long long s, long long e) {
    if (left[id] == 0 && s + 1 < e) {
      // Create children
      left[id] = ++nodes;
      right[id] = ++nodes;
      assert(nodes < MX);
    }
    // apply according to lazy
    t[id] += (e - s) * lazy[id];
    if (s + 1 < e) {
      // propagate to children
      lazy[left[id]] += lazy[id];
      lazy[right[id]] += lazy[id];
    }
    // clear lazy
    lazy[id] = 0;
  }

  void update (int id, long long s, long long e, long long l, long long r, long long value) {
    push(id, s, e);
    if (s >= r || e <= l) return;
    if (s >= l && e <= r) {
      lazy[id] += value; // accumulate lazy
      push(id, s, e);
      return;
    }
    long long m = (s + e) / 2;
    update(left[id], s, m, l, r, value);
    update(right[id], m, e, l, r, value);
    // operation
    t[id] = comb(t[left[id]], t[right[id]]);
  }

  long long query (int id, long long s, long long e, long long l, long long r) {
    push(id, s, e);
    if (s >= l && e <= r) { // return full segment
      return t[id];
    }
    long long m = (s + e) / 2;
    if (r <= m) {
      return query(left[id], s, m, l, r);
    } else if (l >= m) {
      return query(right[id], m, e, l, r);
    }
    return comb(query(left[id], s, m, l, r), query(right[id], m, e, l, r)); // operation
  }
  
  void update (long long l, long long r, long long value) { update(1, 0, n, l, r, value); }
  long long query(long long l, long long r) { return query(1, 0, n, l, r); }
};
