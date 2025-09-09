/*
Iterative Segment Tree, $0$-based indexing\\
Use \texttt{SegTree<Node, N> sg(n)} where $N$ is constant and complete the struct \texttt{Node}
---
Source: https://codeforces.com/blog/entry/18051
*/

template <class Node, int N> struct SegTree { // [l, r) - 0-based

  Node t[N << 1];

  void build() {
    for (int i = N - 1; i > 0; i--)
      t[i] = t[i << 1] + t[i << 1 | 1];
  }

  void update(int i, const Node &val) {
    for (t[i += N] = val; i >>= 1;)
      t[i] = t[i << 1] + t[i << 1 | 1];
  }

  Node query(int l, int r) {
    Node ansl, ansr;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = ansl + t[l++];
      if (r & 1)
        ansr = ansr + t[--r];
    }
    return ansl + ansr;
  }
};

struct Node {
  Node() = default;
  friend Node operator+(Node &l, Node &r) {};
};
