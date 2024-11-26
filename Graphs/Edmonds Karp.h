/*
Edmonds Karp Algorithm for max flow.\\
Complexity: $O(|V||E|^2)$
---
Source: Me
Verification: https://codeforces.com/gym/567608/problem/H
*/

struct EdmondsKarp
{

    struct Edge
    {
        int v;
        ll flow, capacity;
        // Index in adj[v] where we can found the residual edge
        int residual; // Refer to the residual edge -> adj[v][residual]
        Edge(int v, ll flow, ll capacity, int residual) : v(v), flow(flow), capacity(capacity), residual(residual){};
    };

    vector<vector<Edge>> g;
    int n, s, t;
    ll maxFlow = 0;
    vpi p;
    vl dist;
    ll INF = 1e18;

    EdmondsKarp(vector<vpl> &adj, int n, int s, int t)
    {
        this->n = n;
        this->s = s;
        this->t = t;
        g.resize(n + 5);
        forn(i, n)
        {
            int u = i + 1;
            for (auto [v, len] : adj[u])
            {
                g[u].pb({v, 0, len, g[v].size()});
                g[v].pb({u, 0, 0, g[u].size() - 1});
            }
        }
        ll bt = 0;
        do
        {
            p.assign(n + 5, {-1, -1});
            dist.assign(n + 5, INF);
            bt = bfs();
            maxFlow += bt;
        } while (bt != 0);
    }

    ll bfs()
    {
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while (len(q))
        {
            int u = q.front();
            q.pop();
            if (u == t)
                break;
            forn(i, len(g[u]))
            {
                auto e = g[u][i];
                if (dist[e.v] > dist[u] + 1 && e.capacity > 0)
                {
                    dist[e.v] = dist[u] + 1;
                    q.push(e.v);
                    p[e.v] = {u, i};
                }
            }
        }
        if (dist[t] == INF)
            return 0ll;
        ll bt = INF;
        for (int u = t; p[u].f != -1; u = p[u].f)
            bt = min(bt, g[p[u].f][p[u].s].capacity);
        for (int u = t; p[u].f != -1; u = p[u].f)
            augmentEdge(g[p[u].f][p[u].s], bt);

        return bt;
    }

    void augmentEdge(Edge &e, ll x)
    {
        e.flow += x;
        g[e.v][e.residual].flow -= x;
        e.capacity -= x;
        g[e.v][e.residual].capacity += x;
    }
};
