/*
Knuth Optimization. Optimiza una DP de la forma:
$$dp_{i, j} = \min_{k \in [i, j-1]} \{ dp_{i, k} + dp_{k+1, j} + C(i,j) \}$$
De $O(n^3)$ a $O(n^2)$.
Condiciones:
\begin{itemize}
\item $C(a,c) + C(b,d) \le C(a,d) + C(b,c)$  (cuadrilátero / Monge)
\item $opt_{i, j-1} \le opt_{i, j} \le opt_{i + 1, j}$  (monotonía del óptimo)
\end{itemize}
---

*/

const long long INF = 1e18;

// C[i][j] = costo de combinar intervalo [i, j]
// dp[i][j] = costo mínimo
// opt[i][j] = índice k que da el mínimo óptimo

void knuth_dp(const vector<vector<long long>> &C,
              vector<vector<long long>> &dp) {
  int n = (int)C.size();
  vector<vector<int>> opt(n, vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    dp[i][i] = 0;
    opt[i][i] = i;
  }

  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len - 1 < n; i++) {
      int j = i + len - 1;
      dp[i][j] = INF;

      int start = opt[i][j - 1];
      int end = opt[i + 1][j];
      if (start > end)
        swap(start, end);

      for (int k = start; k <= end; k++) {
        long long val = dp[i][k] + dp[k + 1][j] + C[i][j];
        if (val < dp[i][j]) {
          dp[i][j] = val;
          opt[i][j] = k;
        }
      }
    }
  }
}
