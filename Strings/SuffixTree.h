/**
 * Suffix Tree implementation
 * Complexity: 
 *  - Build: O(|Text|)
 *  - Search patterns: O(|Patterns| + |Matches|)
 * 
 * Sources: KACTL Issues
 * 
 * Verification: Coursera assignment
 * 
 * How to:
 *  - Tree.t is the tree itself
 *  - Tree.t[v].next is a map with outgoing edges
 *  - Take into a account that a edge have a entire label.
 */

struct SuffixTree {
    
    enum { MAXN = 5000 };

	string s;
	int n, sz = 1;

	struct Node {
		int l, r, par, link, leafs;
		map<char,int> next;
		Node(int l=0, int r=0, int par=-1)
			: l(l), r(r), par(par), link(-1), leafs(-1) {};
		int size() { return r - l; };
		int& get(char c) {
			if (!next.count(c)) next[c] = -1;
			return next[c];
		};
	};

    Node t[MAXN*2+5];

	struct State { int v, pos; }; 

    State ptr{0,0};

	State go(State st, int l, int r) {
		while (l < r)
			if (st.pos == t[st.v].size()) {
				st = {t[st.v].get(s[l]), 0};
				if (st.v == -1) return st;
			}
			else {
				if (s[t[st.v].l + st.pos] != s[l])
					return {-1, -1};
				if (r-l < t[st.v].size() - st.pos)
					return {st.v, st.pos + r-l};
				l += t[st.v].size() - st.pos;
				st.pos = t[st.v].size();
			}
		return st;
	}

	int split(State st) {
		if (st.pos == t[st.v].size()) return st.v;
		if (st.pos == 0) return t[st.v].par;
		Node v = t[st.v];
		int id = sz++;
		t[id] = Node(v.l, v.l+st.pos, v.par);
		t[v.par].get(s[v.l]) = id;
		t[id].get(s[v.l+st.pos]) = st.v;
		t[st.v].par = id;
		t[st.v].l += st.pos;
		return id;
	}

	int link(int v) {
		if (t[v].link != -1) return t[v].link;
		if (t[v].par == -1) return 0;
		int to = link(t[v].par);
		return t[v].link = split(go({to,t[to].size()}, t[v].l + !t[v].par, t[v].r));
	}

	void extend(int pos) { for(;;) {
		State nptr = go(ptr, pos, pos+1);
		if (nptr.v != -1) {
			ptr = nptr;
			return;
		}
		int mid = split(ptr), leaf = sz++;
		t[leaf] = Node(pos, n, mid);
		t[mid].get(s[pos]) = leaf;
		ptr.v = link(mid);
		ptr.pos = t[ptr.v].size();
		if (!mid) break;
	}}

    int countLeafsDFS(int u) {
        if (t[u].leafs != -1) return t[u].leafs;
        int leaf = 0, valid = 0;
        for (auto w: t[u].next) {
            int to = w.s;
            if (to != -1) {
                valid++;
                leaf += countLeafsDFS(to);
            }
        }
        if (!valid) leaf = 1;
        return t[u].leafs = leaf;
    }

	SuffixTree(int n) : n(n) {}
	SuffixTree(string s) : n(len(s)) { trav(c, s) append(c); countLeafsDFS(0); }
	void append(char c) { s += c; extend(len(s)-1); }

	// example: find longest common substring
	pi best;
	int lcs(Node& node, int i1, int i2, int olen) {
		if (node.l <= i1 && i1 < node.r) return 1;
		if (node.l <= i2 && i2 < node.r) return 2;
		int mask = 0, len = olen + (node.r - node.l);
		trav(pa, node.next)
			mask |= lcs(t[pa.second], i1, i2, len);
		if (mask == 3)
			best = max(best, {len, node.r - len});
		return mask;
	}
	static pi LCS(string s, string t) {
		SuffixTree st(s + '\1' + t + '\2');
		st.lcs(st.t[0], len(s), len(s) + 1 + len(t), 0);
		return st.best;
	}

};