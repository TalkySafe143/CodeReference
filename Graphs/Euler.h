/*
Euler tour for general graphs in $O(|V|+|E|)$.
---
Source: cp-algo
*/

struct Euler {
	int n; 
	vi path, indeg, outdeg, S, T;
	bool exist = false;
	vector<vi> g;

	Euler(vector<vi> &adj, int sz) : n(sz), g(adj) {
		indeg.assign(n+1, 0);
		outdeg.assign(n+1, 0);
		forn(i, n) {
			int u = i+1;
			outdeg[u] = len(adj[u]);
			for (auto v: adj[u]) indeg[v]++;
		}
		int badV = 0;
		forn(i, n) {
			int u = i+1;
			if (outdeg[u] == indeg[u]+1) S.pb(u);
			if (indeg[u] == outdeg[u]+1) T.pb(u);
			if (indeg[u] != outdeg[u]) badV++;
		}

		if (badV <= 2 and len(S) <= 1 and len(T) <= 1) exist = true;
	};	

	void construct() {
		if (!exist) return;
		stack<int> st; st.push((len(S) ? S.back() : 1));
		while (len(st)) {
			int u = st.top();
			if (!len(g[u])) {
				path.pb(u);
				st.pop();
			} else {
				st.push(g[u].back());
				g[u].pop_back();
			}
		}

		forn(i, n) {
			int u = i+1;
			if (len(g[u])) {
				exist = false;
				return;
			}
		}
		reverse(all(path));
	}
};
