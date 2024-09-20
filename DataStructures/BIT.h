/**
 * Fenwick Tree
 *
 * Sources: Cp-algorithms
 *  - https://cp-algorithms.com/data_structures/fenwick.html#
 *
 * Verification: *
**/


struct BITZero { // Get and Range query - Zero-based indexing - Linear Construction
    int n;
    vi bit;

    BITZero(int n) {
        this->n = n; bit.assign(n, 0);
    }

    BITZero(vi &a) : BITZero(len(a)) {
        forn(i, n) { bit[i] += a[i]; int r = i | (i+1); if (r < n) bit[r] += bit[i]; }
    }

    // Going down in tree to get sum
    int sum(int i) { int ans = 0; for (; i >= 0; i = (i & (i+1))-1) ans += bit[i]; return ans; }

    // Going up in tree to update
    void update(int i, int delta) { for (; i < n; i = i | (i+1)) bit[i] += delta; }

    int rangeSum(int i, int j) { return sum(j)-sum(i); };
}


struct BIT { // Get and Range query - One-based indexing
    int n;
    vi bit;

    BIT() : n(0) {};

    BIT(int n) {
        this->n = n+1;
        bit.assign(n+1, 0);
    }

    BIT(vi &a) : BIT(len(a)) {
        forn(i, n) update(i, a[i]);
    }

    void update(int i, int delta) {
        while (i < n) {
            bit[i] += delta;
            i += (i&(-i)); // Go up in the tree by LB
        }
    }

    // Compute the prefix sum [1, i]
    int sum(int i) {
        int ans = 0;
        while (i > 0) {
            ans += bit[i];
            i -= (i &(-i)); // Go down in the tree by LB
        }
        return ans;
    }

    // Compute the sum of [i, j]
    int rangeSum(int i, int j) {
        return sum(j)-sum(i);
    }
};

struct BITUpdate { // Range Update and Get query
    int n;
    vi bit;

    BITUpdate(int n) {
        this->n = n+1;
        bit.assign(n+1, 0);
    }

    BITUpdate(vi &a) : BITUpdate(len(a)) {
        forn(i, n) updateRange(i, i, a[i]);
    }

    void update(int i, int delta) {
        while (i < n) {
            bit[i] += delta;
            i += (i & (-i));
        }
    }

    void updateRange(int l, int r, int delta) {
        update(l, delta); update(r+1, -delta);
    }

    int get(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= (i&(-i));
        }
        return sum;
    }
};

struct BITRQU { // Range Update and Range Query
    int n;
    BIT a, b;

    BITRQU(int n) {
        this->n = n+1;
        a = BIT(n); b = BIT(n);
    }

    BITRQU(vi &a) : BITRQU(len(a)) {
        forn(i, n) updateRange(i, i, a[i]);
    }

    void updateRange(int l, int r, int delta) {
        a.update(l, delta); a.update(r+1, -delta);
        b.update(l, delta*(l-1)); b.update(r+1, -delta*r);
    }

    int prefixSum(int i) { return a.sum(i)*i - b.sum(i); }

    int rangeSum(int l, int r) { return prefixSum(r)-prefixSum(l); };
};
