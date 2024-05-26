/*
    Computes one MST of a given Graph
    The result MST will be in 'result' vector and total cost in costMST variable.
    Need DSU data structure. DataStructures/Trees/DSU.h 

    Sources: Me

    Verification: *

    Complexity: O(|E|log |V|)
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
    }


    void computeMST() {
        sort(all(edges));
        for (auto e: edges) {
            if (disjoint.find_set(e.u) != disjoint.find_set(e.v)) {
                costMST += e.w; disjoint.union_sets(e.u, e.v);
                result.pb(e);
            }
        }
    }
};