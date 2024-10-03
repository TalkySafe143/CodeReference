/*
Solves the equation: $$ax + by = gcd(a, b)$$. Where $a$, $b$, and $c$ are constants. Solve for $x$ and $y$.
*/

struct ExtendedEuclidean {
    int x, a, b, y;
    ExtendedEuclidean(int a, int b) : b(b), a(a) {}
    int init() {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        ExtendedEuclidean s(b, a%b);
        int d = s.init();
        x = s.y;
        y = s.x - s.y * (a / b);
        return d;
    }
};