
struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point(const Point &p) : x(p.x), y(p.y) {}
  Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
  Point operator * (double c) const { return Point(x * c, y * c ); }
  Point operator / (double c) const { return Point(x / c, y / c ); }

  // for convex hull
  bool operator < (const Point &p) const {
    // return x < p.x || (x == p.x && y < p.y);
    return x < p.x - EPS || (abs(x - p.x) <= EPS && y < p.y - EPS);
  }
  bool operator == (const Point &p) const {
    // return x == p.x && y == p.y;
    return abs(x - p.x) <= EPS && abs(y - p.y) <= EPS;
  }
};
