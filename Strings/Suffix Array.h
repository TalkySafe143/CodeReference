/*
Suffix Array, \texttt{c} is the classes array and \texttt{p} is the suffix array containing the first index in the suffix 0-based index \\
Complexity: $O(|S|\log |S|)$.
---
Source: Me
Verification: *
*/

template <int N> struct SuffixArray {
  int n, l, p[N], c[N], cpy[N], cnt[N], p_new[N];
  string s;

  void clear() {
    fill(p, p + n, 0);
    fill(c, c + n, 0);
  }

  bool equal(int a, int b) {
    return c[a] == c[b] and c[(a + (l >> 1)) % n] == c[(b + (l >> 1)) % n];
  }

  void build_class() {
    int cnt = 0;
    cpy[p[0]] = cnt;

    for (int i = 1; i < n; i++)
      cpy[p[i]] = equal(p[i], p[i - 1]) ? cnt : ++cnt;

    copy(cpy, cpy + n, c);
  }

  void counting_sort(bool second) {
    fill(cnt, cnt + n + 1, 0);
    for (int i = 0; i < n; i++) {
      cnt[c[i] + 1]++;
    }
    for (int i = 1; i < n; i++)
      cnt[i] += cnt[i - 1];

    for (int i = 0; i < n; i++)
      p_new[cnt[c[(p[i] + (l >> 1) * second) % n]]++] = p[i];

    copy(p_new, p_new + n, p);
  }

  void radix_sort() {
    if (l == 1) {
      sort(p, p + n, [&](int a, int b) { return s[a] < s[b]; });
      return;
    }
    counting_sort(true);
    counting_sort(false);
  }

  void build(string &str) {
    s = str + "$";
    n = (int)s.size();
    clear();
    iota(p, p + n, 0);
    for (int i = 0; i < n; i++)
      c[i] = (int)s[i];

    for (l = 1; l >> 1 < n; l <<= 1) {
      radix_sort();
      build_class();
    }
  }
};
