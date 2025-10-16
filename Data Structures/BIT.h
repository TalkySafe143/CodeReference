/*
Fenwick Tree.
Complexity: $O(\log n)$ for both update and query, for building the tree it is
$O(n\log n)$. or $O(n)$ filled with 0's.
---
Sources: Cp-algorithms
 - https://cp-algorithms.com/data_structures/fenwick.html#
Verification: *
*/

struct BIT { // Get and Range query - One-based indexing
  int n = 0;
  vector<int> bit;

  BIT() = default;

  BIT(int n) {
    this->n = n + 1;
    bit.assign(n + 1, 0);
  }

  BIT(vector<int> &a) : BIT((int)a.size()) {
    for (int i = 0; i < n; i++)
      update(i, a[i]);
  }

  void update(int i, int delta) {
    while (i < n) {
      bit[i] += delta;
      i += (i & (-i)); // Go up in the tree by LB
    }
  }

  // Compute the prefix sum [1, i]
  int sum(int i) {
    int ans = 0;
    while (i > 0) {
      ans += bit[i];
      i -= (i & (-i)); // Go down in the tree by LB
    }
    return ans;
  }

  // Compute the sum of [i, j]
  int rangeSum(int i, int j) { return sum(j) - sum(i); }
};

struct BITUpdate { // Range Update and Get query
  int n;
  vector<int> bit;

  BITUpdate(int n) {
    this->n = n + 1;
    bit.assign(n + 1, 0);
  }

  BITUpdate(vector<int> &a) : BITUpdate((int)a.size()) {
    for (int i = 0; i < n; i++)
      updateRange(i, i, a[i]);
  }

  void update(int i, int delta) {
    while (i < n) {
      bit[i] += delta;
      i += (i & (-i));
    }
  }

  void updateRange(int l, int r, int delta) {
    update(l, delta);
    update(r + 1, -delta);
  }

  int get(int i) {
    int sum = 0;
    while (i > 0) {
      sum += bit[i];
      i -= (i & (-i));
    }
    return sum;
  }
};

struct BITRQU { // Range Update and Range Query
  int n;
  BIT a, b;

  BITRQU(int n) {
    this->n = n + 1;
    a = BIT(n);
    b = BIT(n);
  }

  BITRQU(vector<int> &a) : BITRQU((int)a.size()) {
    for (int i = 0; i < n; i++)
      updateRange(i, i, a[i]);
  }

  void updateRange(int l, int r, int delta) {
    a.update(l, delta);
    a.update(r + 1, -delta);
    b.update(l, delta * (l - 1));
    b.update(r + 1, -delta * r);
  }

  int prefixSum(int i) { return a.sum(i) * i - b.sum(i); }

  int rangeSum(int l, int r) { return prefixSum(r) - prefixSum(l); };
};
