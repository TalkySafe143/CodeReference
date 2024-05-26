/*
    Computes one MST of a given Graph
    Use a priority queue

    Sources: Me

    Verification: *

    Complexity: O(|E|log |V|)
*/

struct Prim {
    
    struct Edge {
        int u, v, w;

        Edge(int a, int b, int q) : u(a), v(b), w(q) {};
        bool operator <(Edge &oth) const { return this->w < oth.w; }
    };

    vector<Edge> edges, result;
    vi cost;
    double costMST = 0;
    const int INF = 1e8;
    
    Prim(vpi adj[], int n) {
        cost.assign(n+5, INF);
        cost[1] = 0;
        vector<bool> enqueue(n+5, false);
        vi p(n+5, -1);
        pqg<pi> q;
        q.push({0, 1});
        while (len(q)) {
            auto S = q.top(); q.pop();
            double len_u = S.f; int u = S.s;
            if (len_u > cost[u]) continue;
            if (p[u] != -1) {
                result.pb(Edge(p[u], u, len_u));
                costMST += len_u;
            }
            enqueue[u] = true;
            for (auto [v, len_v]: adj[u]) {
                if (!enqueue[v] && cost[v] > len_v) {
                    cost[v] = len_v; p[v] = u;
                    q.push({cost[v], v});
                }
            }
        }    
    }
};