/*
LCP array
Complexity: $O(|S|\log |S|)$ for Suffix Array computation and $O(|S|)$ for the
LCP computation. Need SuffixArray.h
---
Source: Me
Verification: *
*/

constexpr int N = 4e5 + 5;
SuffixArray<N> suff;

vector<int> compute_lcp() {
  vector<int> lcp(suff.n);
  int k = 0;
  for (int i = 0; i < suff.n - 1; i++) {
    // id es la posicion de p en la que esta el sufijo que empieza en i
    int id = suff.c[i];
    int prev = id - 1;

    while (suff.s[i + k] == suff.s[suff.p[prev] + k])
      k++;
    lcp[id] = k;
    k = max(k - 1, 0);
  }
  return lcp;
}
