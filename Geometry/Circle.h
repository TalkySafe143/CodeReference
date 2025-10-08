/*
2D circle functions and struct
---
Source: Own & Geometry Handbook Lecomte
*/

typedef long double T;

const T EPS = 1e-8L;
const T E0 = 0.0L; // Keep 0 for integer, otherwise EPS

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
