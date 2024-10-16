/*
Disjoint Set Union data structure.
Complexity for \textbf{Find}, \textbf{Union} and \textbf{Make Set}: $O(\alpha(n))$ where $\alpha(n)$ is the inverse Ackermann function.
Ackermann function grows very slowly, so it can be considered constant. It defines like this: $\alpha(n) = \min\{k \geq 0 : A(k, k) > n\}$ where $A(k, k)$ is the Ackermann function.
---
Sources: CP_algorithms & Me
    https://cp-algorithms.com/data_structures/disjoint_set_union.html
Verification: https://judge.yosupo.jp/problem/unionfind
*/

struct DSU {
    vi rank, parent;

    DSU () {};

    DSU(int n) {
        rank.resize(n+1);
        parent.resize(n+1);
        forn(i, n) make(i+1);
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void make(int v) {
        parent[v] = v; rank[v] = 0;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
};
