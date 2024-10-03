/*
Prefix function to KMP
Complexity: $O(|P|)$.
*/

vi prefixFunction(string &P) {
	vi s(len(P));
	s[0] = 0;
	int border = 0;
	for (int i = 1; i < len(P); i++) {
		while (border > 0 && P[i] != P[border]) border = s[border-1];
		if (P[i] == P[border]) border++;
		else border = 0;
		s[i] = border;
	}
	return s;
}
