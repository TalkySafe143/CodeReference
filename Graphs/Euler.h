/*
Euler tour for general graphs in $O(|V|+|E|)$.
---
Source: cp-algo
*/

struct Euler {
  int n;
  vector<int> path, indeg, outdeg, S, T;
  bool exist = false;
  vector<vector<int>> g;

  Euler(vector<vector<int>> &adj, int sz) : n(sz), g(adj) {
    indeg.assign(n + 1, 0);
    outdeg.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
      int u = i + 1;
      outdeg[u] = len(adj[u]);
      for (auto v : adj[u])
        indeg[v]++;
    }
    int badV = 0;
    for (int i = 0; i < n; i++) {
      int u = i + 1;
      if (outdeg[u] == indeg[u] + 1)
        S.pb(u);
      if (indeg[u] == outdeg[u] + 1)
        T.pb(u);
      if (indeg[u] != outdeg[u])
        badV++;
    }

    if (badV <= 2 and len(S) <= 1 and len(T) <= 1)
      exist = true;
  };

  void construct() {
    if (!exist)
      return;
    stack<int> st;
    st.push((len(S) ? S.back() : 1));
    while (not st.empty()) {
      int u = st.top();
      if (!len(g[u])) {
        path.pb(u);
        st.pop();
      } else {
        st.push(g[u].back());
        g[u].pop_back();
      }
    }

    for (int i = 0; i < n; i++) {
      int u = i + 1;
      if ((int)(g[u].size())) {
        exist = false;
        return;
      }
    }
    reverse(path.begin(), path.end());
  }
};
