// requires point.cpp

// Minkowski sum in O(n + m)
// A and B should be in anti-clockwise order
inline bool compare(Point a, Point b) {
  // first lowest, then most to the left
  if(a.y < b.y) return 1;
  if(a.y == b.y) return a.x < b.x;
  return 0;
}

vector<Point> minkow_sum(const vector<Point>& a, const vector<Point>& b) {
  vector<Point> out;
  int lena = int(a.size());
  int lenb = int(b.size());
  int i = 0, j = 0;
  for (int q = 0; q < lena; ++q) if (compare(a[q], a[i])) i = q;
  for (int q = 0; q < lenb; ++q) if (compare(b[q], b[j])) j = q;
  long long pr;
  int nxti, nxtj;
  do {
    out.push_back(a[i] + b[j]);
    nxti = (i + 1) % lena;
    nxtj = (j + 1) % lenb;
    pr = (a[nxti] - a[i]).cross(b[nxtj] - b[j]);
    if (pr > 0) i = nxti;
    else if (pr < 0) j = nxtj;
    else i = nxti, j = nxtj; // paralelas, subo en ambas
  } while(!(a[i] + b[j] == out[0]));
  return out;
}
