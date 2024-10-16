/*
Computes one MST of a given Graph. The result MST will be in \texttt{result} vector and total cost in $costMST$ variable.
Need DSU data structure.
Complexity: $O(|E|log |V|)$.
---
Sources: Me
Verification: https://judge.yosupo.jp/problem/minimum_spanning_tree
*/


struct Kruskal {

    struct Edge {
        int u, v, w;

        Edge(int a, int b, int q) : u(a), v(b), w(q) {};

        bool operator <(Edge& oth) const {
            return this->w < oth.w;
        }
    };

    vector<Edge> edges, result;
    DSU disjoint;
    int costMST = 0;

    Kruskal(vpi adj[], int n) {
        disjoint = DSU(n);
        forn(i, n) for (auto [v, len_v]: adj[i+1]) edges.push_back(Edge(i+1, v, len_v));
        computeMST();
    }


    void computeMST() {
        sort(all(edges));
        for (auto e: edges) {
            if (disjoint.find(e.u) != disjoint.find(e.v)) {
                costMST += e.w; disjoint.unite(e.u, e.v);
                result.pb(e);
            }
        }
    }
};
