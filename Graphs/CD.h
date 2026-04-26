/*
Centroid decomposition. Run DFS first to precompute sizes
---
Source: Me
*/
constexpr int N = 2e5 + 3;

int sz[N], n, parent[N], is_removed[N];
vector<int> adj[N], decomp[N];

void dfs(int u, int p) {
  sz[u] = 1;
  for (auto v : adj[u]) {
    if (v == p)
      continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}

int centroid(int u, int p, int tree_sz) {
  for (auto v : adj[u]) {
    if (v == p or is_removed[v])
      continue;
    if (sz[v] * 2LL > tree_sz) {
      sz[u] -= sz[v];
      sz[v] += sz[u];
      return centroid(v, u, tree_sz);
    }
  }

  is_removed[u] = 1;

  for (auto v : adj[u]) {

    if (is_removed[v])
      continue;

    decomp[u].emplace_back(centroid(v, u, sz[v]));
    parent[decomp[u].back()] = u;
  }
  return u;
}


