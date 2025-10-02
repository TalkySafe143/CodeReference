/*
Implements college Gauss Jordan. Solves $A * x = b$. If there are multiple
solutions, an arbitrary one is returned. Returns rank, or $-1$ if no solutions.
Data in $A$ and $b$ is lost.\\
Complexity: $O(n^2m)$\\
How to: \\
\begin{itemize}
\item $A$ is the matrix with equations coeffs.
\item $b$ is the solution vector.
\item $x$ is the vector where $x_i$ is a variable to solve.
\item Call \texttt{solveLinear} and get $x$.
\end{itemize}
---
Source: KACTL -
https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/SolveLinear.h
Verification: Coursera assignment
*/

const ld eps = 1e-12;
int solveLinear(vector<vd> &A, vd &b, vd &x) {
  int n = len(A), m = len(x), rank = 0, br, bc;
  if (n)
    assert(len(A[0]) == m);
  vi col(m);
  iota(all(col), 0);

  forn(i, n) { // rep(i, 0, n)
    double v, bv = 0;
    for (int r = i; r < n; r++)
      for (int c = i; c < m; c++)
        if ((v = fabs(A[r][c])) > bv)
          br = r, bc = c, bv = v;
    if (bv <= eps) {
      for (int j = i; j < n; j++)
        if (fabs(b[j]) > eps)
          return -1;
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    forn(j, n) swap(A[j][i], A[j][bc]);
    bv = 1 / A[i][i];
    for (int j = i + 1; j < n; j++) {
      double fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      for (int k = i + 1; k < m; k++)
        A[j][k] -= fac * A[i][k];
    }
    rank++;
  }

  x.assign(m, 0);
  for (int i = rank; i--;) {
    b[i] /= A[i][i];
    x[col[i]] = b[i];
    forn(j, i) b[j] -= A[j][i] * b[i];
  }
  return rank; // (multiple solutions if rank < m)
}
