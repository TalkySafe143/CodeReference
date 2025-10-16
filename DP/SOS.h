/*
SOS DP memory optimized. Build in $O(N \cdot 2^N)$
---
Source: USACO
*/

// Build
vector<int> sos = a; // 2^N items
for (int i = 0; i < n; i++) {
  for (int x = 0; x < (1 << n); x++) {
    if (x & (1 << i)) {
      sos[x] += sos[x ^ (1 << i)];
    }
  }
}

// Restore
vector<int> a = sos;
for (int i = 0; i < n; i++) {
  for (int mask = 0; mask < (1 << n); mask++) {
    if (mask & (1 << i))
      a[mask] -= a[mask ^ (1 << i)];
  }
}
