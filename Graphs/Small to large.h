/*
Small to large merge. $O(n\log n)$.\\
swap in \texttt{array} and policy based data structures do not work. For policy based use \texttt{a.swap(b)}
---
Source: own
Verification: https://cses.fi/problemset/task/1139
*/

const int N = 200005;
struct SubTree {
  void merge(SubTree &x) {} // how to merge two subtrees
  int size() {}             // how to know the size
};

SubTree a[N];

void dfs(int u, int p) {
  for (auto v : adj[u]) {
    if (v == p)
      continue;
    dfs(v, u);
    if (a[v].size() > a[u].size())
      swap(a[u], a[v]);
    a[u].merge(a[v]);
  }
  // do whatever
}
