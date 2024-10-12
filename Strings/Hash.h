/*
Computes the Hash and make range queries of the hash.\\
For build $O(|s|)$ and $O(1)$ per query.
*/

class HashedString {
  private:
	static const ll M = 1e9 + 9;
	static const ll B = 9973;
 
	// pow[i] contains B^i % M
	static vl pow;
 
	// p_hash[i] is the hash of the first i characters of the given string
	vl p_hash;
 
  public:
	HashedString(const string &s) : p_hash(len(s) + 1) {
		while (len(pow) < len(s)) { pow.pb((pow.back() * B) % M); } 
		p_hash[0] = 0;
		forn(i, len(s)) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}
 
	ll get_hash(int start, int end) {
		long long raw_val =
		    (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
};
vl HashedString::pow = {1};