/*
Iterative Segment Tree
---
You can watch this video for better understanding: https://www.youtube.com/watch?v=Oq2E2yGadnU
*/

struct SegTree { // [l, r)
    int n;
    vl t;
    ll neut = 2e18;

    SegTree(int n) : n(n) {
        t.assign((n<<1), neut);
    }

    ll combine(ll &a, ll &b) { return min(a, b); }

    void build(vl &a) {
        for(int i = n; i < (n<<1); i++) t[i]=a[i-n];
        for(int i = n-1; i > 0; --i) t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    void update(int idx, ll val) {
        for (t[idx += n]=val; idx > 1; idx >>= 1) t[idx>>1]= combine(t[idx], t[idx^1]);
    }

    ll query(int l, int r) {
        ll ans = neut;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ans = combine(t[l++], ans);
            if (r&1) ans = combine(t[--r], ans);
        }
        return ans;
    }
};
