/*
TSP Dynamic programming. For arbitrary start execute solve(0, -1), for forced
start execute solve((1<<i), i) and append manually to the path.\\ Call buildPath
with the same parameters. Complexity: $O(n^2\cdot 2^n)$.
---
Source:
https://github.com/ProgramacionCompetitivaUFPS/notebook/blob/master/c%2B%2B/Dynamic%20programming/Traveling%20Salesman%20Problem.cpp
Verification: Coursera Assigment.
*/

struct TSP { // 0-based index
  vector<vector<ll>> dist, dp;
  const ll INF = 1e17;
  int N, t, s = 0;
  vector<int> path;

  TSP() = default;
  TSP(int n) : N(n) {
    dist.assign(n, vl(n, INF));
    dp.assign((1 << N) + 2, vl(n, -1));
    t = (1 << N) - 1;
  }
  TSP(vector<vector<pair<ll, ll>>> &adj, int n) : N(n) {
    dist.assign(n, vector<ll>(n, INF));
    dp.assign((1 << N) + 2, vl(n, -1));
    for (int i = 0; i < n; i++)
      for (auto e : adj[i])
        dist[i][e.f] = e.s;
    t = (1 << N) - 1;
  }

  ll solve(int mask, int u) {
    if (mask == t)
      return dist[u][s];
    if (u == -1) {
      ll ans = INF;
      for (int i = 0; i < N; i++)
        s = i, ckmin(ans, solve(mask | (1 << i), i));
      return ans;
    }
    ll &ans = dp[mask][u];
    if (ans != -1)
      return ans;
    ans = INF;
    for (int i = 0; i < N; i++)
      if (!(mask & (1 << i)))
        ckmin(ans, solve(mask | (1 << i), i) + dist[u][i]);
    return ans;
  }

  void buildPath(int mask, int u) {
    if (mask == t)
      return;
    if (u == -1) {
      for (int i = 0; i < N; i++) {
        if (solve(mask, u) == solve(mask | (1 << i), i)) {
          path.push_back(i);
          s = i;
          buildPath(mask | (1 << i), i);
          return;
        }
      }
      return;
    }
    for (int i = 0; i < N; i++) {
      if (!(mask & (1 << i))) {
        if (solve(mask, u) == solve(mask | (1 << i), i) + dist[u][i]) {
          path.push_back(i);
          buildPath(mask | (1 << i), i);
          return;
        }
      }
    }
  }
};
