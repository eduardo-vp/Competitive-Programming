// source: https://cp-algorithms.com/linear_algebra/linear-system-gauss.html

typedef long double db;
const db eps = 1e-9;
const int inf = 2; // just more than 1 is needed

// returns number or solutions (0, 1 or inf)
int gauss (vector< vector<db> > a, vector<db> &ans) {
  int n = a.size();
  int m = int(a[0].size()) - 1;
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int piv = row;
    for (int i = row; i < n; ++i) {
      if (abs(a[i][col]) > abs(a[piv][col])) {
        piv = i;
      }
    }
    if (abs(a[piv][col]) < eps) continue;
    
    for (int i = col; i <= m; ++i) {
      swap(a[row][i], a[piv][i]);
    }
    where[col] = row;
    for (int i = 0; i < n; ++i) if (i != row) {
      db factor = a[i][col] / a[row][col];
      for (int j = col; j <= m; ++j) {
        a[i][j] -= a[row][j] * factor;
      }
    }
    row++;
  }

  ans.assign(m, 0);
  bool ind = false;
  for (int i = 0; i < m; ++i){ 
    if (where[i] != -1) {
      ans[i] = a[where[i]][m] / a[where[i]][i];
    } else ind = true;
  }
  for (int i = 0; i < n; ++i) {
    db sum = 0;
    for (int j = 0; j < m; ++j) {
      sum += ans[j] * a[i][j];
    }
    if (abs(sum - a[i][m]) > eps) return 0; // this eq failed
  }
  if (ind) return inf; // at least one independent variable
  return 1;
}

