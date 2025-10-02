/*
In a tree, compute \textit{binary jump} table for a rooted tree\\
Complexity: $O(\log n)$.
---
Source: Own
Verification: https://codeforces.com/gym/101889/problem/I
*/

struct BinaryLifting {

  vector<vector<int>> adj, table;
  vector<int> parent, lvl;
  vector<bool> vis;
  int n, K;

  BinaryLifting(vector<vector<int>> &g, int n_, int root) : n(n_), adj(g) {
    vis.assign(n + 5, false);
    parent.assign(n + 5, -1);
    lvl.assign(n + 5, 0);
    K = log2(n) + 1;
    table.assign(K, vi(n + 5, -1));

    dfs(root, -1, 0);
    for (int k = 1; k < K; k++) {
      for (int i = 1; i <= n; i++) {
        int mid = table[k - 1][i];
        if (mid != -1) {
          table[k][i] = table[k - 1][mid];
        }
      }
    }
  }

  int walk(int u, int k) { // Walk k edges from u to the root.
    for (int i = 0; i < K; i++)
      if ((1 << i) & k)
        u = table[i][u];
    return u;
  }

  int lca(int u, int v) {
    if (lvl[u] > lvl[v])
      u = walk(u, lvl[u] - lvl[v]);
    if (lvl[v] > lvl[u])
      v = walk(v, lvl[v] - lvl[u]);
    if (u == v)
      return u;
    for (int k = K - 1; k >= 0; k--) {
      if (table[k][u] != table[k][v]) {
        u = table[k][u]; // Take the jump
        v = table[k][v];
      }
    }
    return table[0][u];
  }

  void dfs(int u, int p, int d) {
    vis[u] = true;
    lvl[u] = d;
    for (auto v : adj[u]) {
      if (!vis[v] && v != p) {
        dfs(v, u, d + 1);
        parent[v] = u;
        table[0][v] = u;
      }
    }
  }
};
