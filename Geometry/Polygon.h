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

vector<Point> convex_hull_collinear(vector<Point> v) {
  vector<Point> hull;

  sort(v.begin(), v.end(), [&](const Point &a, const Point &b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  });

  int rep = 2;
  int sz = 0;
  while (rep--) {
    for (auto i : v) {
      while ((int)hull.size() - sz > 1 and
             orient(end(hull)[-2], hull.back(), i) > 0) {
        hull.pop_back();
      }
      hull.push_back(i);
    }
    hull.pop_back();
    sz = (int)hull.size();
    reverse(v.begin(), v.end());
  }

  return hull;
}

// This convex hull do not take any collinear points
vector<Point> buildHull(vector<Point> v) {

  if ((int)v.size() < 3)
    return v;

  int ind = int(min_element(v.begin(), v.end(),
                            [&](const Point &a, const Point &b) {
                              return make_pair(a.x, a.y) < make_pair(b.x, b.y);
                            }) -
                v.begin());
  vector<Point> hull{v[ind]};
  vector<int> candidate;

  for (int i = 0; i < (int)v.size(); i++)
    if (v[i] != v[ind])
      candidate.push_back(i);

  sort(candidate.begin(), candidate.end(), [&](int a, int b) {
    T o = orient(v[ind], v[a], v[b]);
    return o != 0 ? o > 0 : (v[a] - v[ind]).sq() < (v[b] - v[ind]).sq();
  });

  for (auto i : candidate) {
    while ((int)hull.size() > 1 and
           orient(end(hull)[-2], hull.back(), v[i]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(v[i]);
  }

  return hull;
}
