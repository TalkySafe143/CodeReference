/*
Stable sum to reduce relative error in non-negative sum\\
Get the roots of quadratic equation
---
Source: Geometry Handbook Lecomte
*/

struct StableSum {
  int n = 0;
  vector<double> v, pref{0};

  void operator+=(double a) {
    assert(a >= 0);
    int s = ++n;
    while (s % 2 == 0) {
      a += v.back();
      v.pop_back(), pref.pop_back();
      s >>= 1;
    }
    v.push_back(a);
    pref.push_back(pref.back() + a);
  }

  double val() { return pref.back(); }
};


int generalEquation(double a, double b, double c, pair<double, double> &ans) {
  assert(a != 0);
  double delta = b * b - 4 * a * c;
  if (delta < 0)
    return 0; // No hay soluciones en R

  double sum = (b >= 0) ? -b - sqrt(delta) : -b + sqrt(delta);
  ans = make_pair(sum / (2 * a), sum == 0 ? 0 : (2 * c) / sum);
  return 1 + (delta > 0);
}

// Assumes p vector of Points. with integer coordinates
tuple<T, Point, Point>
closest (int l, int r)
{
  if (r - l == 1)
    {
      return {LLONG_MAX, p[l], Point{}};
    }

  if (r - l == 2)
    {
      return {dist (p[l], p[l + 1]), p[l], p[l + 1]};
    }

  int m = midpoint (l, r);

  auto sol_l = closest (l, m);
  auto sol_r = closest (m, r);

  T delta = min (get<0> (sol_l), get<0> (sol_r));
  Point a, b;
  if (delta == get<0> (sol_l))
    {
      a = get<1> (sol_l);
      b = get<2> (sol_l);
    }
  else
    {
      a = get<1> (sol_r);
      b = get<2> (sol_r);
    }

  vector<int> c;

  for (int i = l; i < r; i++)
    {
      auto pnt = p[i];
      T dx = abs (p[i].x - p[m].x);
      if (dx * dx < delta)
	c.push_back (i);
    }

  sort (c.begin (), c.end (),
	[] (int idx_a, int idx_b) { return p[idx_a].y > p[idx_b].y; });

  int sz = (int) c.size ();
  for (int i = 0; i < sz; i++)
    {
      for (int k = i + 1;
	   abs (p[c[i]].y - p[c[k]].y) * abs (p[c[i]].y - p[c[k]].y) <= delta
	   and k < sz;
	   k++)
	{
	  T d = dist (p[c[i]], p[c[k]]);
	  if (d < delta)
	    {
	      delta = d;
	      a = p[c[i]];
	      b = p[c[k]];
	    }
	}
    }
  return make_tuple (delta, a, b);
}
