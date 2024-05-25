/*
    Compute the shortest path from S

    For dense graphs, use the second constructor.

    Sources: Me & Cp-algorithms

    Verification: *

    Complexity: O((|V|+|E|)log |V|) or O(|V|^2)
*/


struct Dijkstra {
    const ll INF = 1e18;
    vl dist;
    vi p;
    
    void buildPath(int V, vi& path) {
        path.pb(V);
        for (V = p[V]; V != -1; V = p[V]) path.pb(V);
        reverse(all(path));
    }

    Dijkstra(vpl adj[], int n, int S) {
        dist.assign(n+5, INF);
        p.assign(n+5, -1);
        pqg< pi > q;
        q.push({0, S});
        dist[S] = 0;
        while (len(q)) {
            auto dist_v = q.top().f;
            auto v = q.top().s;
            q.pop();

            if (dist_v > dist[v]) continue;

            for (auto [u, len_u]: adj[v]) {
                if (dist[v] + len_u < dist[u]) {
                    dist[u] = dist[v] + len_u;
                    p[u] = v;
                    q.push({dist[u], u});
                }
            }
        }
    }

    Dijkstra(vpl adj[], int n, int S, bool dense) {
        dist.assign(n+5, INF);
        p.assign(n+5, -1);
        vector<bool> vis(n+5, false);

        dist[S] = 0;

        forn(i, n) {
            int v = -1;
            forn(j, n) {
                if (!vis[j] && (v == -1 || dist[j] < dist[v]))
                    v = j;
            }

            if (dist[v] == INF) break;

            vis[v] = true;

            for (auto [u, len_u]: adj[v]) {
                if (dist[v] + len_u < dist[u]) {
                    p[u] = v;
                    dist[u] = dist[v] + len_u;
                }
            }
        }
    }
};