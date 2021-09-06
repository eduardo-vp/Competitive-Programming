// sort a vector of tuples (represented as vectors)
// it can return a vector of pair<vector,int> where pair.second = initial position

vector< vector<int> > Radixsort(vector< vector<int> > &vec){
  int lmax = 0, m = 0;
  for(vector<int> &v : vec){
    lmax = max(lmax,sz(v));
    for(int &x : v) m = max(m,x+1);
  }
  deque<int> dq;
  vector< queue<int> > q(m);
  vector< vector<int> > hold(lmax);
  for(int i = 0; i < sz(vec); ++i){
    hold[sz(vec[i])-1].pb(i);
  }
  for(int i = lmax-1; i >= 0; --i){
    for(int x : hold[i]) dq.push_front(x);
    while(sz(dq)){
      int x = dq.front();
      dq.pop_front();
      q[vec[x][i]].push(x);
    }
    for(int j = 0; j < m; ++j){
      while(sz(q[j])){
        dq.push_back(q[j].front());
        q[j].pop();
      }
    }
  }
  vector< vector<int> > ans(sz(vec));
  for(int i = 0; i < sz(vec); ++i){
    int x = dq.front(); dq.pop_front();
    ans[i] = vec[x];
  }
  return ans;
}


