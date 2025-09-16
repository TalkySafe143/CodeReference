/*
Lazy segment tree. Complete the \texttt{Op} and \texttt{Node} structs.
*/

template <class Node, class Op> struct LazySegTree { // [l, r) - 0-based

  vector<Node> t;
  vector<Op> lazy;
  int N;

  LazySegTree(int n) {
    N = 1;
    while (N < n)
      N <<= 1;
    t.assign(N << 1, Node());
    lazy.assign(N << 1, Op());
  }

  int mid(int lx, int rx) { return lx + ((rx - lx) >> 1); }
  void pull(int v) { t[v] = t[v << 1] + t[v << 1 | 1]; }
  void push(int v) {
    // early return salva vidas :^)
    t[v] *= lazy[v];
    if (v < N) { // not leaf
      lazy[v << 1] *= lazy[v];
      lazy[v << 1 | 1] *= lazy[v];
    }
    lazy[v] = Op();
  }

  void build(vector<Node> &a, int v, int lx, int rx) {
    t[v].sz = rx - lx;
    if (lx + 1 == rx) {
      if ((int)a.size() > lx)
        t[v] = a[lx];
      return;
    }
    int m = mid(lx, rx);
    build(a, v << 1, lx, m);
    build(a, v << 1 | 1, m, rx);
    pull(v);
  }
  void build(vector<Node> &a) { build(a, 1, 0, N); }

  void update(int v, int lx, int rx, int l, int r, Op incr) {
    t[v].sz = rx - lx;
    push(v);
    if (lx >= r or rx <= l)
      return;
    if (lx >= l and rx <= r) {
      lazy[v] = incr;
      push(v);
      return;
    }
    int m = mid(lx, rx);
    update(v << 1, lx, m, l, r, incr);
    update(v << 1 | 1, m, rx, l, r, incr);

    pull(v);
  }
  void update(int l, int r, Op incr) { update(1, 0, N, l, r, incr); }

  Node query(int v, int lx, int rx, int l, int r) {
    t[v].sz = rx - lx;
    push(v);
    if (lx >= r or rx <= l)
      return Node();
    if (lx >= l and rx <= r)
      return t[v];

    int m = mid(lx, rx);
    return query(v << 1, lx, m, l, r) + query(v << 1 | 1, m, rx, l, r);
  }
  Node query(int l, int r) { return query(1, 0, N, l, r); }
};

struct Op { // Operation for lazy update
  Op() = default;
  Op &operator*=(const Op &a) { // How combine lazy operations
    return *this;
  }
};

struct Node {
  int sz = 0;
  Node() = default;
  friend Node operator+(Node l, Node r) {
  };
  Node &operator*=(const Op &a) { // How do you apply lazy operations
    return *this;
  }
};
