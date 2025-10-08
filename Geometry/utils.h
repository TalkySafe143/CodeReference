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
