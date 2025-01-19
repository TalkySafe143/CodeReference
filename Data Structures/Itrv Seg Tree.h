/*
Iterative Segment Tree, $0$-based indexing\\
Use \texttt{SegTree<Info> sg(n)} and complete the struct \texttt{Info}
---
You can watch this video for better understanding: https://www.youtube.com/watch?v=Oq2E2yGadnU
*/

template< class Info >
struct SegTree { // [l, r)
    int n;
    vector<Info> t;

    SegTree(int n) : n(n) {
        t.assign((n<<1), Info());
    }

    void build(vector<Info> &a) {
        for(int i = n; i < (n<<1); i++) t[i]=a[i-n];
        for(int i = n-1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    void update(int idx, Info val) {
        for (t[idx += n]=val; idx > 1; idx >>= 1) t[idx>>1]= (t[idx] + t[idx^1]);
    }

    Info query(int l, int r) {
        Info ans = Info();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ans = t[l++]+ans;
            if (r&1) ans = t[--r]+ans;
        }
        return ans;
    }
};

struct Info {


    Info(){}; // Define this as NEUTRAL
    friend Info operator +(const Info& a, const Info& b) { // Define this as combine
    } 
};
