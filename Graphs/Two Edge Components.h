/*
Builds the Two Edge Components of a graph. Two vertex lies in the same TECC iff exist at least two edge-disjoint paths between them. Builds a tree where the edges are bridges. $O(|V| + |E|)$
---
Source: https://youkn0wwho.academy/topic-list/articulation_points
*/


struct TECC { // 0 indexed
  int n, k;
  vector<vector<int>> g, t;
  vector<bool> used;
  vector<int> comp, ord, low;
  using edge = pair<int, int>;
  vector<edge> br;
  void dfs(int x, int prv, int &c) {
    used[x] = 1;
    ord[x] = c++;
    low[x] = n;
    bool mul = 0;
    for (auto y : g[x]) {
      if (used[y]) {
        if (y != prv || mul)
          low[x] = min(low[x], ord[y]);
        else
          mul = 1;
        continue;
      }
      dfs(y, x, c);
      low[x] = min(low[x], low[y]);
    }
  }
  void dfs2(int x, int num) {
    comp[x] = num;
    for (auto y : g[x]) {
      if (comp[y] != -1)
        continue;
      if (ord[x] < low[y]) {
        br.push_back({x, y});
        k++;
        dfs2(y, k);
      } else
        dfs2(y, num);
    }
  }
  TECC(const vector<vector<int>> &g)
      : g(g), n(g.size()), used(n), comp(n, -1), ord(n), low(n), k(0) {
    int c = 0;
    for (int i = 0; i < n; i++) {
      if (used[i])
        continue;
      dfs(i, -1, c);
      dfs2(i, k);
      k++;
    }
  }
  void build_tree() {
    t.resize(k);
    for (auto e : br) {
      int x = comp[e.first], y = comp[e.second];
      t[x].push_back(y);
      t[y].push_back(x);
    }
  }
};
