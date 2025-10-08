/*
2D point functions and struct
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
