
struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}
    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double c) const { return Point(x * c, y * c ); }
    Point operator / (double c) const { return Point(x / c, y / c ); }
};

double dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
double norm2(Point p) { return dot(p, p); }
double norm(Point p) { return sqrt(norm2(p)); }
double cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }
