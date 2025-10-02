/*
Computes one MST of a given Graph. Use a priority queue.
Complexity: $O(|E|log |V|)$.
---
Sources: Me
Verification: https://judge.yosupo.jp/problem/minimum_spanning_tree
*/

struct Prim {

  struct Edge {
    int u, v;
    ll w;

    Edge(int a, int b, ll q) : u(a), v(b), w(q) {};
    bool operator>(const Edge &oth) const { return this->w > oth.w; }
  };

  vector<Edge> result;
  ll costMST = 0;

  Prim(vector<pair<ll, ll>> adj[], int n, int start = 1) {
    vector<bool> vis(n + 5, false);
    vis[start] = true;
    pqg<Edge> q;
    for (auto [v, ln] : adj[start])
      q.push({start, v, ln});
    while (len(q)) {
      Edge S = q.top();
      q.pop();
      if (vis[S.v])
        continue;
      vis[S.v] = true;
      costMST += S.w;
      result.push_back(S);
      for (auto [v, ln] : adj[S.v]) {
        if (!vis[v]) {
          q.push({S.v, v, ln});
        }
      }
    }
  }
};
