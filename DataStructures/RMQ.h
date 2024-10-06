/*
Sparse table for min queries.\\
We only need the segments of length $2^i$, thus, we can query overlapping segments to find min/max.
Complexity: $O(n\log n)$ for build and $O(1)$ for query
*/

struct RMQ { // [l, r] - 0 based index
    
    vector<vl> rmq;
    int n, k;
    ll inf = 1e18;

    RMQ(vl& a) : n(len(a)), k(log2(len(a))+1) {
        rmq.assign(k, vl(n, inf)); forn(i, n) rmq[0][i] = a[i]; // For min
        for (int j = 1; j < k; j++) forn(i, n-(1<<j)+1) rmq[j][i] = min(rmq[j-1][i], rmq[j-1][i + (1<<(j-1))]);
    }
    
    ll query(int l, int r) { 
        int p = 31 - __builtin_clz(r-l+1); // log2(w)
        return min(rmq[p][l], rmq[p][r-(1<<p)+1]); 
    }
};
