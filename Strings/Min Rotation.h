/*
Lexicographically minimal rotation (cyclic shift) of a string in $O(|s|)$.
---
Source: https://github.com/bqi343/cp-notebook
*/

int minRotation(string s) {
	int a = 0, N = len(s); s += s;
	forn(b,N) forn(i,N) { 
		// a is current best rotation found up to b-1
		if (a+i==b || s[a+i]<s[b+i]) { b += max(0,i-1); break; } 
		// b to b+i-1 can't be better than a to a+i-1
		if (s[a+i] > s[b+i]) { a = b; break; } // new best found
	}
	return a;
}