
double dot(Point o, Point p, Point q) {
  return dot(p - o, q - o);
}

double cross(Point o, Point p, Point q) {
  return cross(p - o, q - o);
}

vector<Point> convex_hull(vector<Point> &P){
  sort(P.begin(), P.end());
  P.erase(unique(P.begin(), P.end()), P.end());
  int n = P.size();
  if (n == 1) return P;

  vector<Point> bot = {P[0]};
  for (int i = 1; i < n; ++i) {
    while(bot.size() > 1 && cross(bot[bot.size() - 2], bot.back(), P[i]) <= 0)
      bot.pop_back();
    bot.push_back(P[i]);
  }
  bot.pop_back();

  vector<Point> up = {P[n - 1]};
  for (int i = n - 2; i >= 0; --i) {
    while(up.size() > 1 && cross(up[up.size() - 2], up.back(), P[i]) <= 0)
      up.pop_back();
    up.push_back(P[i]);
  }
  up.pop_back();
  bot.insert(bot.end(), up.begin(), up.end());
  return bot;
}
