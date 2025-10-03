/*
LCP array
Complexity: $O(|S|\log |S|)$ for Suffix Array computation and $O(|S|)$ for the
LCP computation. Need \texttt{SuffixArray.h} and \texttt{RMQ.h} to compute any LCP
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

    // Hay que tener cuidado si estamos concatenando strings
    // La marca no debe ser tenida en cuenta, while (suff.s[i] != marca)
    while (suff.s[i + k] == suff.s[suff.p[prev] + k])
      k++;
    lcp[id] = k;
    k = max(k - 1, 0);
  }
  return lcp;
}

RMQ rmq; // Tener inicializado RMQ con el LCP array

// Retorna el LCP de los sufijos que comienzan en la posicion a y b
int get_lcp(int a, int b) {
  if (a == b) {
    return (int)suff.s.size() - a - 2;
  }
  int l = suff.c[a], r = suff.c[b];
  if (l > r)
    swap(l, r);

  int ans = rmq.query(l + 1, r);
  return ans;
}
