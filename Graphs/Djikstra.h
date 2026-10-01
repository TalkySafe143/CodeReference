/*
Compute the shortest path from $S$, no negative weights.
Complexity: $O(|E|\log |V|)$.
---
Sources: Cp-Algorithms
Verification: *
*/

vector<vector<pair<long long, long long>>> adj;

struct Djikstra{
  const long long INF = 1e18;
  int n;
  vector<long long> dist;
  vector<int> p;

  Djikstra() {
    n = adj.size();
    dist.assign(n, INF);
    p.assign(n, -1);
  }

  void shortestPath(int S) {
      dist[S] = 0;
      priority_queue<pair<long long,long long>, vector<pair<long long ,long long>>, greater<pair<long long, long long>>> q;
      q.push({0, S});
      while (!q.empty()) {
          auto [d_v, v] = q.top();
          q.pop();
          if (d_v != dist[v])
              continue;

          for (auto [to, len] : adj[v]) {

              if (dist[v] + len < dist[to]) {
                  dist[to] = dist[v] + len;
                  p[to] = v;
                  q.push({dist[to], to});
              }
          }
      }   
  }

  vector<int> path(int F){
      vector<int> path;

      for (int v = F; v != -1; v = p[v])
          path.push_back(v);

      reverse(path.begin(), path.end());
      return path;
  }

};


