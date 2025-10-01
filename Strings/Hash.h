/*
Computes the Hash and make range queries of the hash.\\
For build $O(|s|)$ and $O(1)$ per query.
*/
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

constexpr int N = 4e5 + 5;

constexpr int MOD1 = 127657753, MOD2 = 987654319;
const int b_first = uniform_int_distribution<int>(0, MOD1 - 1)(rng),
          b_second = uniform_int_distribution<int>(0, MOD2 - 1)(rng);
pair<int, int> pw[N], ipw[N];

int binpow(long long a, long long b, long long m) {
  long long res = 1;
  a %= m;
  while (b) {
    if (b & 1)
      res = (long long)res * a % m;
    a = (long long)a * a % m;
    b >>= 1;
  }
  return res;
}

void precalc_hash() {
  pw[0] = {1, 1};
  for (int i = 1; i < N; i++) {
    pw[i].first = 1LL * pw[i - 1].first * b_first % MOD1;
    pw[i].second = 1LL * pw[i - 1].second * b_second % MOD2;
  }

  int inverse_b_first = binpow(b_first, MOD1 - 2, MOD1);
  int inverse_b_second = binpow(b_second, MOD2 - 2, MOD2);

  ipw[0] = {1, 1};
  for (int i = 1; i < N; i++) {
    ipw[i].first = 1LL * ipw[i - 1].first * inverse_b_first % MOD1;
    ipw[i].second = 1LL * ipw[i - 1].second * inverse_b_second % MOD2;
  }
}

struct HashString {

  int n;
  string s;
  vector<pair<int, int>> hs; // 1-index
  HashString() = default;

  HashString(string &str) {
    n = (int)str.size();
    s = str;
    hs.emplace_back(0, 0);
    for (int i = 0; i < n; i++) {
      pair<int, int> p;
      p.first = (hs[i].first + 1LL * pw[i].first * s[i] % MOD2) % MOD1;
      p.second = (hs[i].second + 1LL * pw[i].second * s[i] % MOD2) % MOD1;
      hs.push_back(p);
    }
  }

  pair<int, int> get_hash(int l, int r) { // 1-based
    pair<int, int> ans;
    ans.first =
        (hs[r].first - hs[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
    ans.second = (hs[r].second - hs[l - 1].second + MOD2) * 1LL *
                 ipw[l - 1].second % MOD2;
    return ans;
  }
};
