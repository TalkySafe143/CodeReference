/*
SCC using Tarjan's algo. $O(|V| + |E|)$
---
Source: own
Verification: https://judge.yosupo.jp/submission/329635
*/
constexpr int N = 1e5 + 5;

vector<int> adj[N], meta[N];
vector<vector<int>> scc;
int vis[N], tin[N], dp[N], stacked[N], id[N], timer;
stack<int> st;

void tarjan(int u) {
  dp[u] = tin[u] = ++timer;
  vis[u] = 1;
  st.push(u);
  stacked[u] = 1;
  for (auto v : adj[u]) {
    if (vis[v]) {
      if (stacked[v])
        dp[u] = min(dp[u], tin[v]);
    } else {
      tarjan(v);
      dp[u] = min(dp[u], dp[v]);
    }
  }
  if (dp[u] == tin[u]) {
    scc.emplace_back();
    int x;
    do {
      x = st.top();
      st.pop();
      stacked[x] = 0;
      id[x] = (int)scc.size();
      scc.back().push_back(x);
    } while (x ^ u);
  }
}

void build_condensed() {
  for (auto comp : scc) {
    for (auto u : comp) {
      for (auto v : adj[u]) {
        if (id[v] == id[u])
          continue;
        meta[id[u]].emplace_back(id[v]);
      }
    }
  }
}
