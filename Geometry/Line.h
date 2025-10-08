/*
2D line functions and struct
---
Source: Own & Geometry Handbook Lecomte
*/

typedef long double T;

const T EPS = 1e-8L;
const T E0 = 0.0L; // Keep 0 for integer, otherwise EPS


struct Line {
  Point v;
  T c;

  Line(Point v, T c) : v(v), c(c) {}
  Line(T a, T b, T c) : v({b, -a}), c(c) {}
  Line(Point P, Point Q) : v(Q - P), c(cross(v, P)) {}

  T side(Point p) { return cross(v, p) - c; }
  // Distance from P to line
  long double dist(Point p) { return fabsl(side(p)) / v.abs(); };

  // Util cuando se esta trabajando con enteros - Distancia al cuadrado
  long double sqDist(Point p) {
    return side(p) * side(p) / (long double)v.sq();
  }

  // Linea perpendicular que pasa por P
  Line perpLine(Point p) { return {p, p + v.perp()}; }

  // Transladar la linea por un vector t
  Line traslate(Point t) { return {v, c + cross(v, t)}; }

  Line shiftLine(long double delta) { return {v, c + delta * v.abs()}; }

  bool pointsInLineComparator(Point a, Point b) {
    return dot(v, a) < dot(v, b);
  }

  // Retorna false si no es posible y coloca el resultado en out
  bool intersec(Line l, Point &out) {
    T d = cross(this->v, l.v);
    if (d == 0)
      return false;

    out = (l.v * this->c - this->v * l.c) / d;
    return true;
  }
};

Point project(Point p, Line l) {
  T k = l.side(p) / l.v.sq();
  return p - l.v.perp() * k;
}

Point reflect(Point p, Line l) {
  T k = (2.0L * l.side(p)) / l.v.sq();
  return p - l.v.perp() * k;
}

Line bisector(Line a, Line b, bool internal) {
  assert(cross(a.v, b.v) != 0); // No pueden ser paralelas

  T sign = internal ? 1.0L : -1.0L;

  return {a.v / a.v.abs() * sign + b.v / b.v.abs(),
          a.c / a.v.abs() * sign + b.c / b.v.abs()};
}

// true si P esta dentro del disco de diametro AB
bool inDisk(Point a, Point b, Point p) { return dot(a - p, b - p) <= 0; }

// true si P esta en el segmento [AB]
bool onSegment(Point a, Point b, Point p) {
  return orient(a, b, p) == 0 and inDisk(a, b, p);
}

// true si dos segmentos AB y CD tienen un unico punto de intersección, puesto
// en OUT
bool properIntersecSegments(Point a, Point b, Point c, Point d, Point &out) {
  T oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c),
    od = orient(a, b, d);

  if (oa * ob < 0 and oc * od < 0) { // Estan de lados opuestos
    out = (a * ob - b * oa) / (ob - oa);
    return true;
  }
  return false;
}

struct PointComparatorByX {
  bool operator()(const Point &a, const Point &b) const {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  };
};

// Intersection of segments [AB], [CD]. Retorna un set por la posibilidad de
// colinear
set<Point, PointComparatorByX> segmentIntersection(Point a, Point b, Point c,
                                                   Point d) {
  Point out;
  if (properIntersecSegments(a, b, c, d, out))
    return {out};

  set<Point, PointComparatorByX> ans;
  if (onSegment(a, b, c))
    ans.insert(c);
  if (onSegment(a, b, d))
    ans.insert(d);
  if (onSegment(c, d, a))
    ans.insert(a);
  if (onSegment(c, d, b))
    ans.insert(b);

  return ans;
}

// Distancia de P hasta [AB]
T distanceToSegment(Point a, Point b, Point p) {
  if (a != b) {
    Line l(a, b);
    if (l.pointsInLineComparator(a, p) and l.pointsInLineComparator(p, b)) {
      return l.dist(p);
    }
  }
  return min((p - a).abs(), (p - b).abs());
}

// Distancia desde [AB] a [CD]
T segmentToSegmentDistance(Point a, Point b, Point c, Point d) {
  Point dummy;
  if (properIntersecSegments(a, b, c, d, dummy))
    return 0;

  return min({distanceToSegment(a, b, c), distanceToSegment(a, b, d),
              distanceToSegment(c, d, a), distanceToSegment(c, d, b)});
}

