
// declare and assign SQ (square root) and N
// usually handle some global variables here (use a struct to avoid them if necessary)

int block[N];

void add (int pos) {
  
}

void rem (int pos) {
  
}

T solve () {
  
}

vector<int> Mo(vector< pair<ii, int> > query, int n) { // ( (l, r), index )
  for (int i = 0; i < n; ++i) {
    block[i] = i / SQ;
  }
  sort(query.begin(), query.end(), [&](auto a, auto b){
    int la = a.first.first, lb = b.first.first;
    if (block[la] != block[lb]) return la < lb;
    int ra = a.first.second, rb = b.first.second;
    return (block[la] & 1) ? ra > rb : ra < rb;
  });
  int L = 0, R = 0, q = query.size();
  while (R < n) add(R++);
  vector<T> ans(query.size());
  for (int i = 0; i < q; ++i) {
    int l = query[i].first.first, r = query[i].first.second, query_id = query[i].second;
    while (l < L) add(--L);
    while (R < r) add(R++);
    while (L < l) rem(L++);
    while (r < R) rem(--R);
    ans[query_id] = solve();
  }
  return ans;
}
