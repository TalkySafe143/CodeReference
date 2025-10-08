/*
2D polygon functions and struct
---
Source: Own & Geometry Handbook Lecomte
*/

typedef long double T;

const T EPS = 1e-8L;
const T E0 = 0.0L; // Keep 0 for integer, otherwise EPS


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
