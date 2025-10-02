/*
Sparse table for min queries.\\
We only need the segments of length $2^i$, thus, we can query overlapping
segments to find min/max. Complexity: $O(n\log n)$ for build and $O(1)$ for
query
---
Source: Own
Verification: https://codeforces.com/problemset/gymProblem/101522/B
*/

struct RMQ { // [l, r] - 0 based index

  vector<vector<int>> rmq;
  int n, k;
  int oo = numeric_limits<int>::max();

  RMQ(vector<int> &a) : n((int)a.size()), k(log2((int)a.size()) + 1) {
    rmq.assign(k, vector<int>(n, oo));
    for (int i = 0; i < n; i++)
      rmq[0][i] = a[i]; // For min
    for (int j = 1; j < k; j++)
      for (int i = 0; i < n - (1 << j) + 1; i++)
        rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
  }

  ll query(int l, int r) {
    int p = 31 - __builtin_clz(r - l + 1); // log2(w)
    return min(rmq[p][l], rmq[p][r - (1 << p) + 1]);
  }
};
