/*
Prime factorization in $O(\sqrt{n})$. Remember this can be done in for loop $[2, \sqrt{n}]$.
---
Source: https://cp-algorithms.com/algebra/factorization.html#wheel-factorization
*/
vl primes;
vl trial_division4(ll n) {
    vl factorization;
    for (ll d : primes) {
        if (d * d > n)
            break;
        while (n % d == 0) {
            factorization.pb(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.pb(n);
    return factorization;
}
