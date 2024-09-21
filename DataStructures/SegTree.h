/**
  Simplest form of segment tree. Using [l, r) for the queries.
  Complexity: Build $O(n)$
              Query $O(\log n)$
*/

struct SegTree { // [l, r)
	int n;
	vl t;
 
	SegTree(int k) {
		n = 1;
		while (n < k) n <<= 1;
		t.assign(2*n, 0ll);
	}
 
	void build(int v, int lx, int rx, vi& a) {
		if (lx+1 == rx) {
			if (lx < len(a)) t[v] = a[lx]; // We added some elements, make sure we are in actual size
			return;
		}
		int mid = lx + ((rx-lx)>>1);
		build(2*v+1, lx, mid, a);
		build(2*v+2, mid, rx, a);
		t[v] = t[2*v+1]+t[2*v+2];
	}
 
	void build(vi& a) { build(0, 0, n, a); }
 
	void update(int v, int lx, int rx, int val, int i) {
		if (rx-lx == 1) {
			t[v] = val;
			return;
		}
		int mid = lx + ((rx-lx)>>1);
		if (i < mid) update(2*v+1, lx, mid, val, i);
		else update(2*v+2, mid, rx, val, i);
		t[v] = t[2*v+1] + t[2*v+2];
	}
 
	void update(int i, int val) { update(0, 0, n, val, i); }
 
	ll sum(int v, int lx, int rx, int l, int r) {
		if (lx >= r || rx <= l) return 0;
		if (l <= lx && r >= rx) return t[v];
		int mid = lx + ((rx-lx)>>1);
		return sum(2*v+1, lx, mid, l, r)+sum(2*v+2, mid, rx, l, r);
	}
 
	ll sum(int l, int r) { return sum(0, 0, n, l, r); }
};
