/*
Compute LCA in $O(1)$. Need $O(n\log n)$ for build RMQ.
---
Verification: https://codeforces.com/problemset/problem/342/E
*/
int inf = INT_MAX;
struct Node {
  int lvl = inf, v = -1;
  bool operator<(const Node &a) const { return lvl < a.lvl; }
};

struct RMQ { // [l, r] - 0 based index

  vector<vector<Node>> rmq;
  int n, k;
  RMQ() = default;

  RMQ(vector<Node> &a) : n(len(a)), k(log2(len(a)) + 1) {
    rmq.assign(k, vector<Node>(n));
    forn(i, n) rmq[0][i] = a[i]; // For min
    for (int j = 1; j < k; j++)
      forn(i, n - (1 << j) + 1) rmq[j][i] =
          min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
  }

  Node query(int l, int r) {
    int p = 31 - __builtin_clz(r - l + 1); // log2(w)
    return min(rmq[p][l], rmq[p][r - (1 << p) + 1]);
  }
};

struct LCA {
  vector<Node> euler;
  vector<int> lvl, tin;
  vector<bool> vis;
  int n;
  vector<vector<int>> adj;
  RMQ rmq;

  LCA(vector<vi> &g, int sz, int root = 1) : adj(g), n(sz) {
    vis.assign(sz + 5, false);
    lvl.assign(sz + 5, 0);
    tin.assign(sz + 5, 0);
    dfs(root, 0);
    rmq = RMQ(euler);
  }

  void dfs(int u, int l) {
    vis[u] = true;
    lvl[u] = l;
    tin[u] = euler.size();
    euler.push_back({lvl[u], u});
    for (auto v : adj[u]) {
      if (!vis[v]) {
        dfs(v, l + 1);
        euler.push_back({lvl[u], u});
      }
    }
  }

  int query(int u, int v) {
    int f = tin[u], s = tin[v];
    if (f > s)
      swap(f, s);
    return rmq.query(f, s).v;
  }
};
