/*
Simplest form of segment tree. Using [l, r) for the queries.\\
Complexity for \textbf{Build}: $O(n)$ and \textbf{Query}: $O(\log n)$.\\
Use \texttt{SegTree<Info> sg(n)} and complete the struct \texttt{Info}
*/

template <class Info> struct SegTree { // [l, r)
  int n;
  vector<Info> t;

  SegTree(int k) {
    n = 1;
    while (n < k)
      n <<= 1;
    t.assign(2 * n, Info());
  }

  void pull(int v) { t[v] = t[(v << 1)] + t[(v << 1) | 1]; }

  void build(int v, int lx, int rx, vector<Info> &a) {
    if (lx + 1 == rx) {
      if (lx < len(a))
        t[v] = a[lx];
      return;
    }
    int mid = lx + ((rx - lx) >> 1);
    build((v << 1), lx, mid, a);
    build((v << 1) | 1, mid, rx, a);
    pull(v);
  }

  void build(vector<Info> &a) { build(1, 0, n, a); }

  void update(int v, int lx, int rx, Info val, int i) {
    if (rx - lx == 1) {
      t[v] = val;
      return;
    }
    int mid = lx + ((rx - lx) >> 1);
    if (i < mid)
      update((v << 1), lx, mid, val, i);
    else
      update((v << 1) | 1, mid, rx, val, i);
    pull(v);
  }

  void update(int i, Info val) { update(1, 0, n, val, i); }

  Info sum(int v, int lx, int rx, int l, int r) {
    if (lx >= r || rx <= l)
      return Info();
    if (l <= lx && r >= rx)
      return t[v];
    int mid = lx + ((rx - lx) >> 1);
    return sum((v << 1), lx, mid, l, r) + sum((v << 1) | 1, mid, rx, l, r);
  }

  Info sum(int l, int r) { return sum(1, 0, n, l, r); }
};

struct Info {

  Info() {}; // Define this as NEUTRAL
  friend Info operator+(const Info &a,
                        const Info &b) { // Define this as combine
  }
};
