/*
Heavy Light Decomposition. Requires Segment Tree (Lazy by default) \\
Add the edges with \texttt{add_edge()}, update initial values with \texttt{update_path(u, u, x)} after \texttt{init()} was called. !!!! Initialize HLD struct as global to avoid Segmentation fault \\
Operations in $O(\log^2 n)$, only pass through at most $\log n$ light nodes!!
---
Source: Benq
Verfication: CSES
*/

template <int SZ, bool WEIGHT_EDGES> struct HLD {
  int N;
  vector<int> adj[SZ], euler;
  int parent[SZ], top[SZ], depth[SZ], sz[SZ], label[SZ], timer;

  LazySegTree<Node, Op> seg = LazySegTree<Node, Op>(SZ);

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs(int u) {
    sz[u] = 1;

    for (auto &v : adj[u]) {
      parent[v] = u;
      depth[v] = depth[u] + 1;
      adj[v].erase(find(adj[v].begin(), adj[v].end(), u)); // remove parent
      dfs(v);
      sz[u] += sz[v];
      if (sz[v] > sz[adj[u][0]])
        swap(v, adj[u][0]);
    }
  }

  void dfs_hld(int u) {
    label[u] = timer++;
    euler.push_back(u);
    for (auto v : adj[u]) {
      top[v] = (v == adj[u][0] ? top[u] : v);
      dfs_hld(v);
    }
  }

  void init(int n, int root = 1) {
    N = n;
    parent[root] = depth[root] = timer = 0;
    dfs(root);
    top[root] = root;
    dfs_hld(root);
  }

  int lca(int u, int v) {
    for (; top[u] != top[v]; v = parent[top[v]])
      if (depth[top[u]] > depth[top[v]])
        swap(u, v);
    return (depth[u] < depth[v] ? u : v);
  }

  // op callback gives [l, r] range
  template <class BinaryOperation>
  void process_path(int u, int v, BinaryOperation op) {
    for (; top[u] != top[v]; v = parent[top[v]]) {
      if (depth[top[u]] > depth[top[v]])
        swap(u, v);
      op(label[top[v]], label[v]);
    }

    if (depth[u] > depth[v])
      swap(u, v);
    // + boolean because edges val goes down to node connected to the edge
    op(label[u] + WEIGHT_EDGES, label[v]);
  }

  void update_path(int u, int v, long long x) {
    process_path(u, v, [&](int l, int r) {});
  }

  long long query_path(int u, int v) {
    // modify to your operation
    long long res = 0;
    process_path(u, v, [&](int l, int r) {});
    return res;
  }

  void update_subtree(int u, long long x) {
    // update segment tree in range [label[u] + WEIGHT_EDGES, label[u] + sz[u] )
    //
  }
};
