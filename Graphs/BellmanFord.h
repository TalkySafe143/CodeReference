/*
Compute the shortest path from $S$ with negative cycles. Nodes in negative cycles will be in $A$ vector.
Complexity: $O(|V||E|)$.
---
Sources: Me & Cp-algorithms
Verification: *
*/

struct BellmanFord {
    const ll INF = 1e18;
    vl dist;
    vi p, A;

    struct Edge {
        ll a, b, w; // Change this if need memory
    };

    vector<Edge> edges;

    void buildPathNormal(int V, vi &path) {
        path.pb(V);
        for (V = p[V]; V != -1; V = p[V]) path.pb(V);
        reverse(all(path));
    }

    BellmanFord(vpl adj[], int n) {
        dist.assign(n+5, INF);
        p.assign(n+5, -1);
        forn(i, n) for (auto [v, len_v]: adj[i+1]) edges.push_back({i+1, v, len_v});
    }

    void computeShortestPath(int S) {
        dist[S] = 0;

        for (;;) {
            bool any = false;
            for (auto e: edges) {
                if (dist[e.a] < INF) {
                    if (dist[e.a] + e.w < dist[e.b]) {
                        dist[e.b] = dist[e.a] + e.w;
                        p[e.b] = e.a;
                        any = true;
                    }
                }
            }

            if (!any) break;
        }
    }

    bool negativeCycles(int S, int n) {
        dist[S] = 0;
        forn(i, n) {
            for (auto e: edges) {
                if (dist[e.a] < INF) {
                    if (dist[e.a] + e.w < dist[e.b]) {
                        p[e.b] = e.a;
                        dist[e.b] = max(dist[e.a] + e.w, -INF);
                        if (i == n-1) A.pb(e.b);
                    }
                }
            }
        }

        return len(A) > 0;
    }
};