
struct Node {
  // define Node
};

Node merge(Node a, Node b) {
  // define merge
}

struct STree {
  int n;
  vector<Node> t;
  STree(int n): n(n), t(2 * n + 5) {}
  void update(int p, Node x) {
    for (t[p += n] = x; p >>= 1; ) {
      t[p] = merge(t[p << 1], t[p << 1 | 1]);
    }
  }
  Node query(int l, int r) {
    Node ansl, ansr;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ansl = merge(ansl, t[l++]);
      if (r & 1) ansr = merge(t[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};
