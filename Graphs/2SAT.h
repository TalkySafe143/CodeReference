/*
Resuelve el problema de $2$-\textbf{SAT} mediante grafo de implicaciones y componentes fuertemente conexas (SCC).  
Cada variable $x_i$ tiene dos nodos: $i$ (representa $x_i = \text{True}$) y $i+V$ (representa $x_i = \text{False}$).  

La solución es satisfacible si y solo si $\text{SCC}(i) \neq \text{SCC}(i+V)$ para todo $i$.

\begin{enumerate}
\item Complejidad: $O(V + E)$
\item Representación: cada cláusula $(a \lor b)$ se traduce en dos implicaciones $(\lnot a \rightarrow b)$ y $(\lnot b \rightarrow a)$
\item Funciones útiles:
  \begin{itemize}
    \item \texttt{either(a, b)} $\rightarrow (a \lor b)$
    \item \texttt{implies(a, b)} $\rightarrow (\lnot a \lor b)$
    \item \texttt{set\_true(a)}, \texttt{set\_false(a)}
    \item \texttt{xnor(a, b)} $\rightarrow (a \leftrightarrow b)$
    \item \texttt{xorf(a, b)} $\rightarrow (a \oplus b)$
  \end{itemize}
\end{enumerate}

---
*/

struct TwoSAT {
  int V;
  vector<vector<int>> g;
  vector<int> comp, order, assignment;
  bool sat = true;

  TwoSAT(int n) : V(n), g(2 * n + 5) {}

  int neg(int x) { return (x > V ? x - V : x + V); }

  // (a OR b)
  void either(int a, int b) {
    a = (a > 0 ? a : V - a);
    b = (b > 0 ? b : V - b);
    g[neg(a)].push_back(b);
    g[neg(b)].push_back(a);
  }

  // a => b  → (¬a ∨ b)
  void implies(int a, int b) {
    a = (a > 0 ? a : V - a);
    b = (b > 0 ? b : V - b);
    g[neg(a)].push_back(b);
  }

  void set_true(int a)  { either(a, a); }
  void set_false(int a) { either(-a, -a); }

  // (a ↔ b)
  void xnor(int a, int b) {
    implies(a, b);
    implies(b, a);
  }

  // (a ⊕ b)
  void xorf(int a, int b) {
    either(a, b);
    either(-a, -b);
  }

  // Kosaraju SCC
  void dfs1(int v, vector<int>& vis, vector<vector<int>>& gr) {
    vis[v] = 1;
    for (int u : gr[v]) if (!vis[u]) dfs1(u, vis, gr);
    order.push_back(v);
  }

  void dfs2(int v, int c, vector<int>& vis, vector<vector<int>>& grt) {
    vis[v] = 1;
    comp[v] = c;
    for (int u : grt[v]) if (!vis[u]) dfs2(u, c, vis, grt);
  }

  bool solve() {
    int N = 2 * V;
    vector<vector<int>> grt(N + 1);
    for (int v = 1; v <= N; v++) for (int u : g[v]) grt[u].push_back(v);

    vector<int> vis(N + 1, 0);
    for (int i = 1; i <= N; i++) if (!vis[i]) dfs1(i, vis, g);

    comp.assign(N + 1, -1);
    fill(vis.begin(), vis.end(), 0);
    int j = 0;
    reverse(order.begin(), order.end());
    for (int v : order) if (!vis[v]) dfs2(v, ++j, vis, grt);

    assignment.assign(V + 1, 0);
    for (int i = 1; i <= V; i++) {
      if (comp[i] == comp[i + V]) {
        sat = false;
        return false;
      }
      assignment[i] = (comp[i] > comp[i + V]);
    }
    return true;
  }
};

