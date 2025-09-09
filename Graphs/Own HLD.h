/*
Heavy light decomposition functions. Requires Segment Tree \\
Path queries in $O(\log^2 n)$. Start with \texttt{dfs(root, 0, 0); hdl(root, 0);}
---
Source: Own
Verification: https://cses.fi/paste/8a81dd7254047cb1dcf429/
*/

const int N = 2e5 + 5;

vector<int> adj[N];
int in[N], sz[N], depth[N], top[N], parent[N], out[N], w[N], label[N],
    heavy_node[N], euler[N], timer = 0, euler_timer = 0;
SegTree<Node, N> seg;

void dfs(int u, int p, int d) {
  sz[u] = 1;
  depth[u] = d;
  int heavy = 0;
  for (auto v : adj[u]) {
    if (v == p)
      continue;

    parent[v] = u;
    dfs(v, u, d + 1);

    sz[u] += sz[v];
    if (sz[v] > sz[heavy])
      heavy = v;
  }
  heavy_node[heavy] = 1;
}

void hdl(int u, int p) {
  in[u] = timer++;
  label[u] = euler_timer++;
  euler[label[u]] = u;

  // update segtree index label[u] with value w[u]
  //

  top[u] = heavy_node[u] ? euler[label[top[p]]] : u;
  for (auto v : adj[u]) {
    if (v == p or not heavy_node[v])
      continue;
    hdl(v, u);
    break;
  }

  for (auto v : adj[u]) {
    if (v == p or heavy_node[v])
      continue;
    hdl(v, u);
  }
  out[u] = timer++;
}

bool is_ancestor(int u, int v) { return in[u] <= in[v] and out[u] >= out[v]; }

int lca(int u, int v) {
  int low = u;
  while (not is_ancestor(u, v)) { // not ancestor
    low = u;
    u = u == top[u] ? parent[u] : top[u];
  }

  if (not heavy_node[low])
    return u;

  int l = label[u], r = label[low];
  while (l + 1 < r) {
    int m = l + ((r - l) >> 1);
    if (is_ancestor(euler[m], v))
      l = m;
    else
      r = m;
  }

  return euler[l];
}

void hdl_update(int u, long long val) {
  // update the index label[u]
  //
}

long long get_path_value(int u, int v) {
  if (u == v) {
    // return the query to just u
    //
  }
  long long ans = 0;
  // assuming condition initially true
  int low = u;
  while (u != 0 and depth[u] > depth[v]) {
    low = u;
    u = top[u];
    if (depth[u] <= depth[v]) {
      break;
    }

    // update ans querying [label[u], label[low] + 1)
    //

    u = parent[u];
  }

  if (u != 0 and depth[u] <= depth[v]) {
    int l = label[low] - (depth[low] - depth[v]) + 1, r = label[low] + 1;

    // update ans querying [l, r)
    //
  }

  return ans;
}

long long hdl_query(int u, int v) {
  int lca_query = lca(u, v);

  // return u -> lca + v -> lca + lca
  //
}
