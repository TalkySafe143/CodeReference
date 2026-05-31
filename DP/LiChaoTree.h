/*
Lichao tree, gets the best line in a point. $O(\log n)$ because of the segtree.
Remember: If you need floating point, divide the interval in $\epsilon$. If you need not lines but segments, just search for the segments and run add().
---
Source: me
*/
struct Line
{
  long long k, b;

  Line () : k (0), b (LLONG_MAX) {}
  Line (long long k_, long long b_) : k (k_), b (b_) {}
  long long operator() (long long x) { return x * k + b; }
};

namespace lichao {
// In this case, the coords aren't too high, but sparse seg tree
// is also ok
Line t[N << 2];

void
add (int v, int lx, int rx, Line l)
{
  int mid = midpoint (lx, rx);
  int dominate_mid = (l (mid) < t[v](mid));
  if (dominate_mid)
    swap (l, t[v]);

  if (lx + 1 == rx)
    return;

  int dominate_left = (l (lx) < t[v](lx));
  if (not dominate_left)
    add (v << 1 | 1, mid, rx, l);
  else
    add (v << 1, lx, mid, l);
}

long long
get (int v, int lx, int rx, int x)
{
  if (lx + 1 == rx)
    return t[v](x);

  int mid = midpoint (lx, rx);
  long long val = LLONG_MAX;

  val = (x < mid ? get (v << 1, lx, mid, x) : get (v << 1 | 1, mid, rx, x));

  return min (t[v](x), val);
}

}; // namespace lichao


