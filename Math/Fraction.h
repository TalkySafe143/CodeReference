/*
Fraction class - if its useful (Not all the cases). Represents
$\frac{num}{denom}$\\ Ensure GCC for \_\_int128 and ensure \_\_gcd
---
Source: own
*/

struct Fraction {
  __int128 num = 0, denom = 0;

  Fraction() = default;
  Fraction(__int128 n, __int128 m) : num(n), denom(m) {
    assert(denom != 0);
    reduce(num, denom);
  }

  void reduce(__int128 &a, __int128 &b) {
    __int128 g = __gcd(a, b);
    a /= g;
    b /= g;
  };

  Fraction operator*(Fraction other) const {
    return Fraction(other.num * num, other.denom * denom);
  }

  Fraction operator+(Fraction other) const {
    return Fraction(num * other.denom + other.num * denom, denom * other.denom);
  }

  Fraction operator-(Fraction other) const {
    return Fraction(num * other.denom - other.num * denom, denom * other.denom);
  }

  Fraction operator/(Fraction other) const {
    return Fraction(num * other.denom, denom * other.num);
  };

  bool operator<(const Fraction &other) const {
    __int128 x = num * other.denom, y = other.num * denom;
    return x < y;
  };

  bool operator>(const Fraction &other) const {
    __int128 x = num * other.denom, y = other.num * denom;
    return x > y;
  };

  bool operator>=(Fraction other) const {
    __int128 x = num * other.denom, y = other.num * denom;
    return x >= y;
  };

  bool operator<=(Fraction other) const {
    __int128 x = num * other.denom, y = other.num * denom;
    return x <= y;
  };
  bool operator==(Fraction other) const {
    __int128 x = num * other.denom, y = other.num * denom;
    return x == y;
  };

  bool operator!=(Fraction other) const {
    __int128 x = num * other.denom, y = other.num * denom;
    return x != y;
  };
};
