/*
Computes shortest path for every pair of nodes.\\
Complexity: $O(|V|^3)$.
---
Source: Own
Verification: https://codeforces.com/problemset/problem/1196/F
*/
struct Floyd {

  const ll oo = 1e18;
  vector<vector<ll>> dist;

  Floyd(vector<vector<pair<ll, ll>>> &adj, int n) {
    dist.assign(n + 5, vector<ll>(n + 5, oo));
    for (int i = 0; i < n; i++) {
      dist[i + 1][i + 1] = 0;
      for (auto [v, len] : adj[i + 1])
        dist[i + 1][v] = len;
    }

    for (int z = 1; z <= n; z++) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          // if (d[i][k] < oo && d[k][j] < oo) // if negative cycles
          dist[i][j] = min(dist[i][j], dist[i][z] + dist[z][j]);
        }
      }
    }
  }
};
