/*
---
RT = 5 is primitive root for both common mods
Sources: Benq
    https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/number-theory%20(11.1)/Modular%20Arithmetic/ModInt.h
Verification: https://open.kattis.com/problems/modulararithmetic
*/

template<int MOD> struct mint {
	static const int mod = MOD;
 	int v;
 	explicit operator int() const { return v; }
	mint():v(0) {}
	mint(ll _v):v(int(_v%MOD)) { v += (v<0)*MOD; }
	mint& operator/=(const mint& o) { return (*this) *= inv(o); }
	mint& operator+=(mint o) {
		if ((v += o.v) >= MOD) v -= MOD;
		return *this; }
	mint& operator-=(mint o) {
		if ((v -= o.v) < 0) v += MOD;
		return *this; }
	mint& operator*=(mint o) {
		v = int((ll)v*o.v%MOD); return *this; }
	friend mint pow(mint a, ll p) { assert(p >= 0);
		return p==0?1:pow(a*a,p/2)*(p&1?a:1); }
	friend mint inv(mint a) { assert(a.v != 0); return pow(a,MOD-2); }
	friend mint operator+(mint a, mint b) { return a += b; }
	friend mint operator-(mint a, mint b) { return a -= b; }
	friend mint operator*(mint a, mint b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
};
