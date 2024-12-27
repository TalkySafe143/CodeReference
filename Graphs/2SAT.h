/*
Solves $2$-SAT problem. The required format for the SAT is construct a CNF described by lines.\\
For example, a clause could be: 1 -4. Indicating that (x_1 OR NOT(x_4)) clause is in CNF.\\
Time complexity: $O(|F|)$ where $F$ is the formula. Requires \textbf{SCC.h}
---
Source: Me.
Verification: Coursera assignment
*/



struct TwoSAT {

    vector<vi> g, meta;
    vi ans;
    int V; // Number Variables
    bool sat = true;
    vector<bool> vis;
    SCC scc;

    // For x and -x nodes, 1 and V+1...
    TwoSAT(vector<vi> &clauses, int w) : V(w) {
        g = vector<vi>(2*V+5);
        ans.assign(2*V+1, 0);
        trav(c, clauses) {

            if (len(c) == 1) {
                int u = (-1)*c[0],v = c[0];
                fixNode(u); fixNode(v);
                g[u].pb(v); 
                continue;
            }

            int u = (-1)*c[0], v = c[1];
            fixNode(u); fixNode(v);
            g[u].pb(v); 

            u = (-1)*c[1],  v= c[0];
            fixNode(u); fixNode(v);
            g[u].pb(v);
        }

        scc = SCC(meta, g, 2*V);

        forn(i, V) {
            if (scc.roots[i+1] == scc.roots[V+i+1]) {
                sat = false;
                break;
            }
        }

        if (sat) assignVariables();
    }

    void fixNode(int &u) {
        if (u < 0) u = V + abs(u);
    }

    void dfs(int u) {
        if (vis[u]) return;
        vis[u] = true;
        for (auto v: meta[u]) dfs(v);
        for (auto c: scc.roots_contains[u]) {
            bool neg = false;
            if (c > V) c -= V, neg = true;
            if (ans[c] != 0) continue;
            ans[c] = (neg ? -1 : 1); 
        }
    }


    void assignVariables() {
        vis.assign(2*V+5, false);
        forn(i, 2*V) {
           dfs(i+1);
        }
    }

};
