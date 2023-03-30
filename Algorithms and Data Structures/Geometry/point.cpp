
struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point(const Point &p) : x(p.x), y(p.y) {}
  Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
  Point operator * (double c) const { return Point(x * c, y * c ); }
  Point operator / (double c) const { return Point(x / c, y / c ); }

  double dot(Point p) { return x * p.x + y * p.y; }
  double norm2() { return this->dot(*this); }
  double norm() { return sqrt(norm2()); }
  double cross(Point p) { return x * p.y - y * p.x; }
  bool left(Point p, Point q) { // is the point to the left of the directed line pq?
    // return (q - p).cross(*this) > 0;
    return (q - p).cross(*this - p) > EPS;
  }

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
