/*
    Cycle finding in a directed graph. 
    If there is a cycle, will be in cycle vector. 1-based nodes.
    Source: CP algorithms
        https://cp-algorithms.com/graph/finding-cycle.html

    Verification: *

    Complexity: O(|E|) for E edges
*/

struct CycleDetection {
    
    bool existCycle;
    // Cycle start & Cycle end
    int cs, ce;
    vi parent;
    vector<char> color;
    vi cycle;
    
    bool dfs(int u, vi adj[]) {
        color[u] = 1;
        for (auto v: adj[u]) {
            if (color[v] == 0) {
                parent[v] = u;
                if (dfs(v, adj)) return true;
            } else if (color[v] == 1){
                ce = u;
                cs = v;
                return true;
            }
        }
        color[u] = 2;
        return false;
    }

    CycleDetection(vi adj[], int n) {
        color.assign(n, 0);
        parent.assign(n, -1);
        cs = -1;
        forn(i, n) if (color[i+1] == 0 && dfs(i+1, adj)) break;

        if (cs == -1) existCycle = false;
        else {
            cycle.pb(cs);
            for (int v = ce; v != cs; v = parent[v]) cycle.pb(v);
            reverse(all(cycle));
            existCycle = true;
        }
    }
};