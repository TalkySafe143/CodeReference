/*
Computes the SCCs (Strongly Connected Components) in a directed graph. Also
computes the Metagraph. The graph must be a DAG (Directed Acyclic Graph).
Complexity: $O(|V| + |E|)$.
---
Sources: CP-algorithms
    https://cp-algorithms.com/graph/strongly-connected-components.html
Verification: https://codeforces.com/contest/894/problem/E
*/

struct SCC {
  vector<bool> vis;
  vector<int> order, component, roots, roots_nodes;
  vector<vector<int>> SCCs, roots_contains;
  int n;

  // Used for topological sort
  void dfs1(int u, vector<vector<int>> &adj) {
    vis[u] = true;
    for (auto v : adj[u])
      if (!vis[v])
        dfs1(v, adj);
    order.push_back(u);
  }

  // Used for build the SCCs
  void dfs2(int u, vector<vector<int>> &adj) {
    vis[u] = true;
    component.push_back(u);
    for (auto v : adj[u])
      if (!vis[v])
        dfs2(v, adj);
  }

  SCC() = default;

  // Constructor for store all components in SCCs vector
  SCC(vector<vector<int>> &adj, int n) {
    this->n = n;
    // Build G^R
    vector<vector<int>> adj_inv(n + 5);
    for (int i = 0; i < n; i++)
      for (auto v : adj[i + 1])
        adj_inv[v].push_back(i + 1);

    vis.assign(n + 5, false);
    for (int i = 0; i < n; i++)
      if (!vis[i + 1])
        dfs1(i + 1, adj);

    vis.assign(n + 5, false);
    reverse(order.begin(), order.end());

    for (auto v : order) {
      if (!vis[v]) {
        dfs2(v, adj_inv);
        SCCs.push_back(component);
        component.clear();
      }
    }
  }

  // Contructor to process SCCs via callback
  SCC(vector<vector<int>> &adj, int n, function<void(vector<int> &)> Process) {

    this->n = n;

    // Build G^R
    vector<vi> adj_inv(n + 5);
    for (int i = 0; i < n; i++)
      for (auto v : adj[i + 1])
        adj_inv[v].pb(i + 1);

    vis.assign(n + 5, false);
    for (int i = 0; i < n; i++)
      if (!vis[i + 1])
        dfs1(i + 1, adj);
    vis.assign(n + 5, false);
    reverse(order.begin(), order.end());

    for (auto v : order) {
      if (!vis[v]) {
        dfs2(v, adj_inv);
        Process(component);
        component.clear();
      }
    }
  }

  // Warning: Initialize the vi inside of adj_scc with size 0.
  SCC(vector<vi> &adj_scc, vector<vi> &adj, int n) {

    // Build G^R
    vector<vi> adj_inv(n + 5);
    adj_scc.resize(n + 5);
    for (int i = 0; i < n; i++)
      for (auto v : adj[i + 1])
        adj_inv[v].pb(i + 1);

    roots.assign(n + 5, 0);

    vis.assign(n + 5, false);
    for (int i = 0; i < n; i++)
      if (!vis[i + 1])
        dfs1(i + 1, adj);
    vis.assign(n + 5, false);
    reverse(order.begin(), order.end());

    for (auto v : order) {
      if (!vis[v]) {
        dfs2(v, adj_inv);
        int root = component.front();
        for (auto u : component)
          roots[u] = root;
        roots_nodes.pb(root);
        component.clear();
      }
    }

    roots_contains.resize(n + 5);
    for (int i = 0; i < n; i++) {
      for (auto u : adj[i + 1]) {
        int root_v = roots[i + 1], root_u = roots[u];
        if (root_u != root_v)
          adj_scc[root_v].push_back(root_u);
      }
      roots_contains[roots[i + 1]].push_back(i + 1);
    }
  }
};
