/*
Min cost flow - Dijkstra with potentials.\\
Complexity: $O(min(|E|^2|V|\log |V|, |E|\log |V| \cdot flow))$\\
Really fast in practice. Some variants:\\
\begin{itemize}
\item Min cost fixed flow: When pushing flow, take care to do not push more than required.
\item Min cost b-flow: Every node have a demand/supply. Just introduce a super source/sink with capacity equals to demand/supply. Finally is fixed flow problem.
\item Min cost any flow: When the shortest path length is non-negative, stops the algorithm
\end{itemize}
---
Source: Own
Verification: https://cses.fi/problemset/task/2129/
*/


struct MinCostDinic {

    struct Edge {
        int u, v;
        ll cap, flow=0, cost;
        bool forward = true;

        Edge(int _u, int _v, ll _cap, ll _cost) : u(_u), v(_v), cap(_cap), cost(_cost) {
        }
    };

    vector<Edge> edges;
    vector<vi> adj;
    int n, m=0;
    int s, t; 
    ll cost=0, maxFlow=0;
    // p is potential
    vl p, dist, lvl, currEdge;
    const ll oo = 1e18;

    MinCostDinic(int sz) : n(sz+3) {
        adj.resize(n);
        p.resize(n);
        s = 0; t = n-1;
    };

    void addEdge(int u, int v, ll cap, ll cost) {
        edges.emplace_back(u, v, cap, cost);
        edges.emplace_back(v, u, 0, -cost);
        adj[u].pb(m); adj[v].pb(m+1);
        edges[m+1].forward = false;
        m += 2;
    }

    void augmentEdge(int a, int b, ll flow) {
        cost += (flow*edges[a].cost);
        edges[a].flow += flow;
        edges[b].flow -= flow;
    }

    void initPotentials() {
        // Bellman ford
        dist.assign(n, oo);
        dist[s] = 0;
        bool relax = true;
        for (int i = 0; i < n and relax; i++) {
            relax = false;
            for (auto e: edges) {
                if (dist[e.u]+e.cost < dist[e.v] and e.cap > 0) {
                    dist[e.v] = dist[e.u]+e.cost;
                    relax = true;
                }
            }
        }

        // Setting potentials
        forn(i, n) if (dist[i] < oo) p[i] = dist[i];
    }

    bool dijkstra() {
        dist.assign(n, oo);
        dist[s] = 0;
        pqg<pl> pq; pq.emplace(dist[s], s);
        while (len(pq)) {
            int u = pq.top().s;
            ll dist_u = pq.top().f;
            pq.pop();
            if (dist_u != dist[u]) continue;

            for (auto id: adj[u]) {
                int v = edges[id].v;
                ll w = edges[id].cost + p[u] - p[v];
                if (dist[u]+w < dist[v] and edges[id].cap - edges[id].flow > 0) {
                    dist[v]=dist[u]+w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        forn(i, n) if (dist[i]<oo) {
            // We have unreal distance in dist
            // In particular we have sum of cost + p[s] - p[i]
            // We need the real distance, so we add p[i] and substract p[s]
            dist[i] += (p[i]-p[s]);
        }

        // Readjust potentials
        forn(i, n) if (dist[i]<oo) p[i] = dist[i];

        return (dist[t] != oo); // for max flow
        // return dist[t] <= 0 // for just min cost flow
    }

    bool inShortestPath(Edge &e) {
        return (e.cost + p[e.u] - p[e.v] == 0ll);
    }

    bool bfs() {
        lvl.assign(n, oo);
        lvl[s] = 0;
        queue<int> q; q.push(s);
        while (len(q)) {
            int u = q.front(); q.pop();
            for (int id: adj[u]) {
                auto e = edges[id];
                int v = e.v;
                if (dist[v] >= oo or !inShortestPath(e)) continue;
                if (lvl[u]+1<lvl[v] and e.cap-e.flow > 0) {
                    lvl[v]=lvl[u]+1;
                    q.push(v);
                }
            }
        }
        return (lvl[t] != oo);
    }

    ll dfs(int u, ll incoming) {
        if (incoming == 0) return 0;
        if (u == t) return incoming;
        for (ll &nxt = currEdge[u]; nxt < len(adj[u]); nxt++) {
            auto e = edges[adj[u][nxt]];

            if (lvl[u]+1 != lvl[e.v] or !inShortestPath(e)) continue;

            ll pushed = dfs(e.v, min(incoming, e.cap-e.flow));
            if (!pushed) continue;

            augmentEdge(adj[u][nxt], adj[u][nxt]^1, pushed);
            return pushed;
        }
        return 0;
    }

    pl flow() {
        initPotentials();
        while (dijkstra()) {
            while (bfs()) {
                currEdge.assign(n, 0);
                while (ll flow = dfs(s, oo)) {
                    maxFlow += flow;
                }
            }
        }
        return {maxFlow, cost};
    };

};
