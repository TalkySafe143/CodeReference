/*
Dinic's algorithm for Max flow.\\
Complexity: $O(|V|^2|E|)$ and $O(|E|\sqrt{V})$ for unit nets.
---
Source: Own & Cp-algorithms
Verification: https://www.codechef.com/problems/KMHAMHA
*/
struct Dinic {

  const ll oo = 1e18;

  struct Edge {
    int u, v;
    ll cap, flow = 0;

    Edge(int u, int v, ll cap) : u(u), v(v), cap(cap) {};
  };

  vector<Edge> edges;

  vector<vector<int>> adj;
  vector<ll> lvl;
  vector<int> currEdge;
  int n = 0, m = 0, s = 0, t;
  ll maxFlow = 0;
  queue<int> q;

  // Source -> 0 and Sink -> n+1
  Dinic(int sz) : n(sz) {
    t = n + 1;
    adj.resize(n + 2);
  }

  void addEdge(int u, int v, ll cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(m);
    adj[v].push_back(m + 1);
    m += 2;
  }

  void augmentEdge(int a, int b, ll flow) {
    edges[a].flow += flow;
    edges[b].flow -= flow;
  }

  bool bfs() {
    lvl.assign(n + 2, oo);
    lvl[s] = 0;
    q.push(s);
    while (len(q)) {
      int s = q.front();
      q.pop();
      for (auto edgeId : adj[s]) {
        Edge e = edges[edgeId];
        if (e.cap - e.flow > 0 and lvl[e.u] + 1 < lvl[e.v]) {
          lvl[e.v] = lvl[e.u] + 1;
          q.push(e.v);
        }
      }
    }
    return (lvl[t] != oo);
  };

  ll dfs(int u, ll incoming) {
    if (!incoming)
      return 0;
    if (u == t)
      return incoming;

    for (int &nxt = currEdge[u]; nxt < len(adj[u]); nxt++) {
      Edge e = edges[adj[u][nxt]];
      if (lvl[u] + 1 != lvl[e.v])
        continue;

      ll pushed = dfs(e.v, min(e.cap - e.flow, incoming));

      if (!pushed)
        continue;

      augmentEdge(adj[u][nxt], adj[u][nxt] ^ 1, pushed);
      return pushed;
    }
    return 0;
  }

  ll flow() {
    while (bfs()) {
      currEdge.assign(n + 2, 0);
      while (ll flow = dfs(s, oo)) {
        maxFlow += flow;
      }
    }
    return maxFlow;
  };
};
