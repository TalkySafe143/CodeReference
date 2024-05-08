/*
    Compute the Topological sort in a directed graph.
    Takes the adj list and graph size (n) for constructor.
    Topological order will be in TopoSort::topo

    Sources: Me

    Verification: *

    Complexity: O(|V| + |E|)
*/

struct TopoSort {
    
    vector<bool> vis;
    vi topo;
    
    void dfs(int u, vi adj[]) {
        vis[u] = true;
        for (auto v: adj[u]) {
            if (!vis[v]) dfs(v, adj);
        }
        topo.pb(u);
    }

    TopoSort(vi adj[], int n) {
        vis.assign(n+5, false);
        forn(i, n) if (!vis[i+1]) dfs(i+1, adj);
        reverse(all(topo));
    }

};