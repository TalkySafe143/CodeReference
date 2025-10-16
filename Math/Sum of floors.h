/*
$\lfloor \frac{C}{i} \rfloor$ have at most $2 \times \sqrt{C}$ different values.
---
Source: https://codeforces.com/blog/entry/108909
*/

ll ans = 0;
for (int l = 1, r; l <= C; l = r + 1) {
  r = C / (C / l);
  ans += 1ll * (r - l + 1) * (C / l);
}
