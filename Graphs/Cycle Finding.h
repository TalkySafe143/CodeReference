/*
Cycle finding in a directed graph. If there is a cycle, will be in
\texttt{cycle} vector. 1-based nodes. Complexity: $O(|E|)$ for $E$ edges.
---
Source: CP algorithms
    https://cp-algorithms.com/graph/finding-cycle.html
Verification: https://codeforces.com/problemset/problem/915/D
*/

struct CycleDetection {

  bool existCycle;
  // Cycle start & Cycle end
  int cs, ce;
  vector<int> parent, cycle, color;

  bool dfs(int u, vector<int> adj[]) {
    color[u] = 1;
    for (auto v : adj[u]) {
      if (color[v] == 0) {
        parent[v] = u;
        if (dfs(v, adj))
          return true;
      } else if (color[v] == 1) {
        ce = u;
        cs = v;
        return true;
      }
    }
    color[u] = 2;
    return false;
  }

  CycleDetection(vector<int> adj[], int n) {
    color.assign(n + 1, 0);
    parent.assign(n + 1, -1);
    cs = -1;
    for (int i = 1; i <= n; i++)
      if (color[i] == 0 && dfs(i, adj))
        break;

    if (cs == -1)
      existCycle = false;
    else {
      cycle.push_back(cs);
      for (int v = ce; v != cs; v = parent[v])
        cycle.push_back(v);
      reverse(cycle.begin(), cycle.end());
      existCycle = true;
    }
  }
};
