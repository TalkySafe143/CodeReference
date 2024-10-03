/*
Suffix Array
Complexity: $O(|S|\log |S|)$.
---
Source: Me
Verification: *
*/

struct SuffixArray {

	vi order, type, s;

	int& operator[](int i) { return s[i]; };
	int size() { return len(s); };

	SuffixArray(string &S) {
		sortCharacters(S, order);
		computeCharClasess(S, order, type);
		int L = 1;
		while (L <= len(S)) {
			sortDoubled(S, L, order, type);
			updateClasses(order, type, L);
			L *= 2;
		}
		s = vi(all(order));
	}

	void updateClasses(vi &order, vi& type, int L) {
		int n = len(order);
		vi newType(n, 0);
		newType[order[0]] = 0;
		forn(i, n-1) {
			int cur = order[i+1], prev = order[i];
			int mid = (cur+L)%n, midPrev = (prev+L)%n;
			if (type[cur] != type[prev] || type[mid] != type[midPrev]) newType[cur] = newType[prev]+1;
			else newType[cur] = newType[prev];
		}
		type = vi(all(newType));
	}

	void sortDoubled(string &S, int L, vi &order, vi& type) {
		int n = len(S);
		vi count(n, 0), newOrder(len(S), 0);
		forn(i, n) count[type[i]]++;
		forn(i, n-1) count[i+1] = count[i+1]+count[i];
		for (int i = n-1; i >= 0; i--) {
			int start = (order[i]-L+n)%n;
			int cl = type[start];
			count[cl]--;
			newOrder[count[cl]] = start;
		}
		order = vi(all(newOrder));
	}

	void sortCharacters(string &S, vi& order) {
		order.assign(len(S), 0);
		vi count(27, 0); // Depende del alfabeto
		forn(i, len(S)) {
			int c = (S[i] == '$' ? 0 : (S[i]-'a')+1);
			count[c]++;
		}
		// Especie de prefix sum para determinar el orden
		forn(i, 26) count[i+1] = count[i+1] + count[i];

		for (int i = len(S)-1; i >= 0; i--) {
			int c = (S[i] == '$' ? 0 : (S[i]-'a')+1);
			count[c]--;
			order[count[c]] = i;
		}
	}

	void computeCharClasess(string &S, vi& order, vi& type) {
		type.assign(len(S), 0);
		type[order[0]] = 0;
		forn(i, len(S)-1) {
			if (S[order[i+1]] != S[order[i]]) type[order[i+1]] = type[order[i]]+1;
			else type[order[i+1]] = type[order[i]];
		}
	}
};
