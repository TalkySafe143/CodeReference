/*
Block cut tree in $O(|V| + |E|)$. Two vertex lies in the same BCC iff exist at least to vertex-disjoint paths beetween them. Call \texttt{dfs(1)} and later \texttt{build_bt(n)}.
---
Source: https://youkn0wwho.academy/topic-list/articulation_points
*/
constexpr int N = 1e5 + 5;

vector<int> g[N], bcc[N], bt[N << 1]; // Warning: always double capacity if you
                                      // are working with BC Tree nodes.
int low[N], tin[N], id[N], art[N << 1], timer = 0, sz_bcc = 0;
stack<int> st;

void dfs(int u, int p) {
  st.push(u);
  tin[u] = low[u] = ++timer;
  for (auto v : g[u]) {
    if (v == p)
      continue;
    if (tin[v] > 0) { // back-edge
      low[u] = min(low[u], tin[v]);
    } else { // spanning-edge
      dfs(v, u);
      low[u] = min(low[v], low[u]);
      if (tin[u] <= low[v]) {
        sz_bcc++;
        int x;
        do {
          x = st.top();
          st.pop();
          bcc[x].emplace_back(sz_bcc);
        } while (x ^ v);
        bcc[u].emplace_back(sz_bcc);
      }
    }
  }
}

void build_bt(int n) {
  for (int i = 1; i <= n; i++) {
    if ((int)bcc[i].size() > 1) { // Articulation point
      id[i] = ++sz_bcc;
      art[id[i]] = 1;
      for (auto v : bcc[i]) {
        bt[v].emplace_back(id[i]);
        bt[id[i]].emplace_back(v);
      }
    } else if ((int)bcc[i].size() == 1)
      id[i] = bcc[i][0];
  }
}
