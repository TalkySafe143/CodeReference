/*
    Disjoint Set Union data structure
    Sources: CP_algorithms & Me
        https://cp-algorithms.com/data_structures/disjoint_set_union.html
    Verification: *
*/

struct DSU {
    vector<int> rank;
    vector<int> parent;

    DSU () {};

    DSU(int n) {
        rank.resize(n+1);
        parent.resize(n+1);
        for (int i = 1; i <= n; i++) make_set(i);
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
};