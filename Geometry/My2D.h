/*
2D geometry functions and structs
---
Source: Own & Geometry Handbook Lecomte
*/

typedef long double T;

const T EPS = 1e-8L;
const T E0 = 0.0L; // Keep 0 for integer, otherwise EPS

struct Point {
  T x, y;
  Point operator+(Point p) { return {x + p.x, y + p.y}; }
  Point operator-(Point p) { return {x - p.x, y - p.y}; }
  Point operator*(T p) { return {x * p, y * p}; }
  Point operator/(T p) { return {x / p, y / p}; }

  friend bool operator==(Point a, Point b) { return a.x == b.x and a.y == b.y; }
  friend bool operator!=(Point a, Point b) { return !(a == b); }
  friend ostream &operator<<(ostream &out, const Point &p) {
    out << "(" << p.x << " , " << p.y << ")";
    return out;
  }

  complex<T> toComplex() { return complex<T>(x, y); }

  T sq() { return x * x + y * y; }
  long double abs() { return sqrtl(sq()); }

  Point translate(Point v) { return *this + v; };
  Point scale(Point c, double factor) { return c + (*this - c) * factor; };

  // From origin
  Point rotate(double phi) {
    return {x * cosl(phi) - y * sinl(phi), x * sinl(phi) + y * cosl(phi)};
  };

  // From center c using complex function
  Point rotate(Point c, double phi) {
    auto C = c.toComplex();
    auto Cis = complex<T>(cosl(phi), sinl(phi));
    auto V = (*this - c).toComplex();

    auto ans = C + (Cis * V);
    return {ans.real(), ans.imag()};
  }

  // Perpendicular
  Point perp() { return {-y, x}; }

  void normalize() {
    T l = abs();
    if (fabsl(l) > EPS) { // != 0 con error
      x /= l;
      y /= l;
    }
  }
};

// Saber el signo de un numero, -1 para negativo, 0 para cero y 1 para positivos
template <typename T> int sgn(T x) { return (T(0) < x) - (x < T(0)); }

template <typename T>
Point linearTransfo(Point p, Point q, Point r, Point fp, Point fq) {
  auto P = p.toComplex(), Q = q.toComplex(), R = r.toComplex();
  auto Fp = fp.toComplex(), Fq = fq.toComplex();

  auto ans = Fp + (R - P) * (Fq - Fp) / (Q - P);
  return {ans.real(), ans.imag()};
}

T dot(Point v, Point w) { return v.x * w.x + v.y * w.y; };

bool isPerp(Point v, Point w) { return dot(v, w) == 0; };

T angle(Point v, Point w) { return atan2(fabsl(cross(v, w)), dot(v, w)); }

T radToDegree(T rads) { return (rads * 180.0L) / M_PI; }

T degreeToRads(T degree) { return (degree * M_PI) / 180.0L; }

T cross(Point v, Point w) { return v.x * w.y - v.y * w.x; };

T orient(Point a, Point b, Point c) { return cross(b - a, c - a); }

// Mira si un punto P esta dentro del ángulo de los vectores AB y AC
bool inAngle(Point a, Point b, Point c, Point p) {
  assert(orient(a, b, c) != 0);
  if (orient(a, b, c) < 0)
    swap(b, c);
  return (orient(a, b, p) >= 0 and orient(a, c, p) <= 0);
}

long double orientedAngle(Point a, Point b, Point c) {
  T rawAngle = angle(b - a, c - a);
  if (orient(a, b, c) < 0)
    rawAngle = 2.0L * M_PI - rawAngle;

  return rawAngle;
}

// Dado un conjunto de puntos, ver si es convexo
bool isConvex(vector<Point> &polygon) {
  int n = len(polygon);
  bool neg = false, pos = false;
  forn(i, n) {
    T o = orient(polygon[i], polygon[(i + 1) % n], polygon[(i + 2) % n]);
    neg |= (o < 0);
    pos |= (o > 0);
  }

  return !(neg and pos);
}

// Polar sort con centro en C y el primer ángulo en I (Default C = (0, 0), I =
// es X+ axis)
void polarSort(vector<Point> &a, Point c = {0, 0}, Point I = {0, 0}) {
  // Retorna true si esta en los dos primeros cuadrantes.
  auto half = [&](Point x) -> bool {
    assert(x.x != 0 or
           x.y != 0); // (0, 0) esta indefinido, porque ded ahí partimos

    if (I == Point{0, 0})
      return (x.y > 0 or (x.y == 0 and x.x < 0));
    return (cross(I, x) < 0 or (cross(I, x) == 0 and dot(I, x) < 0));
  };

  sort(all(a), [&](Point v, Point w) {
    // Longitud como tie-breaker
    return make_tuple(half(v - c), 0.0L, (v - c).sq()) <
           make_tuple(half(w - c), cross(v - c, w - c), (w - c).sq());
  });
}

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

T triangleArea(Point a, Point b, Point c) {
  return fabsl(cross(b - a, c - a)) / 2.0L;
}

T areaPolygon(vector<Point> &p) {
  int n = len(p);
  T area = 0.0L;
  forn(i, n) { area += cross(p[i], p[(i + 1) % n]); }
  return fabsl(area) / 2.0L;
}

// Mira si P esta por encima de A
bool above(Point a, Point p) { return p.y >= a.y; }

// Mira si [PQ] cruza el rayo al infinito de A
bool crossesRay(Point p, Point q, Point a) {
  return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

// Mira si A esta en el poligono **general**
// Si strict es true, retorna false cuando A esta en el limite
bool pointInPolygon(Point a, vector<Point> &p, bool strict = true) {
  int cnt = 0;
  int n = len(p);
  forn(i, n) {
    if (onSegment(p[i], p[(i + 1) % n], a)) {
      return !strict;
    }
    cnt += crossesRay(p[i], p[(i + 1) % n], a);
  }
  return cnt & 1;
}

struct Circle {
  Point O;
  T r;

  Circle(Point o, T r) : O(o), r(r) {}

  // Circumcircle in the triangle ABC
  Circle(Point a, Point b, Point c) {
    b = b - a, c = c - a;
    assert(cross(b, c) != 0);

    Point AO = (b * c.sq() - c * b.sq()).perp() / cross(b, c) / 2.0L;
    r = AO.abs();
    O = AO + a;
  }

  // Retorna el numero de intersecciones
  int lineIntersection(Line l, pair<Point, Point> &out) {
    T h2 = r * r - l.sqDist(O);
    if (h2 >= 0) { // La linea toca al circulo
      Point p = project(O, l);
      Point h = l.v * sqrt(h2) / l.v.abs();
      out = {p - h, p + h};
    }
    return 1 + sgn(h2);
  }

  // Retorna el numero de intersecciones
  int circleIntersection(Circle c, pair<Point, Point> &out) {
    Point d = c.O - O;
    T d2 = d.sq();
    if (d2 == 0.0L)
      return 0; // Los circulos son similares
    T pd = (d2 + r * r - c.r * c.r) / 2.0L;
    T h2 = r * r - pd * pd / d2;
    if (h2 >= 0.0L) {
      Point p = O + d * pd / d2, h = d.perp() * sqrt(h2 / d2);
      out = {p - h, p + h};
    }
    return 1 + sgn(h2);
  }

  // Retorna el numero de tangentes
  // Se puede colocar un c2 de r = 0 para tomar un tangente que pase por un
  // punto.
  int tangents(Circle c2, bool inner, vector<pair<Point, Point>> &out) {
    if (inner)
      c2.r *= -1.0L;

    Point d = c2.O - O;
    T dr = r - c2.r, d2 = d.sq(), h2 = d2 - dr * dr;
    if (d2 == 0.0L or h2 < 0) {
      return 0;
    }
    for (T sign : {-1, 1}) {
      Point v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
      out.push_back({O + v * r, c2.O + v * c2.r});
    }
    return 1 + (h2 > 0);
  }
};
