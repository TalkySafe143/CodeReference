/*
TSP Dynamic programming. For arbitrary start execute solve(0, -1), for forced start execute solve((1<<i), i) and append manually to the path.\\
Call buildPath with the same parameters.
Complexity: $O(n^2\cdot 2^n)$.
---
Source: https://github.com/ProgramacionCompetitivaUFPS/notebook/blob/master/c%2B%2B/Dynamic%20programming/Traveling%20Salesman%20Problem.cpp
Verification: Coursera Assigment.
*/


struct TSP { // 0-based index
    vector<vl> dist, dp;
    const ll INF = 1e17;
    int N, t, s=0;
    vi path;

    TSP() = default;
    TSP(int n) : N(n) {
        dist.assign(n, vl(n, INF)); dp.assign((1<<N)+2, vl(n, -1));
        t = (1<<N)-1;
    }
    TSP(vector<vpl> &adj, int n) : N(n) {
        dist.assign(n, vl(n, INF)); dp.assign((1<<N)+2, vl(n, -1));
        forn(i, n) for (auto e: adj[i]) dist[i][e.f] = e.s;
        t = (1 << N) -1;
    }
    
    ll solve(int mask, int u) {
        if (mask == t) return dist[u][s];
        if (u == -1) {
            ll ans = INF;
            forn(i, N) s=i, ckmin(ans, solve(mask|(1<<i),i));
            return ans;
        }
        ll &ans = dp[mask][u];
        if (ans != -1) return ans;
        ans = INF;
        forn(i, N) if (!(mask & (1<<i))) ckmin(ans, solve(mask|(1<<i), i)+dist[u][i]);
        return ans;
    }

    void buildPath(int mask, int u) {
        if (mask == t) return;
        if (u == -1) {
            forn(i, N) {
                if (solve(mask, u) == solve(mask | (1<<i), i)) {
                    path.pb(i);
                    s=i;
                    buildPath(mask | (1<<i), i);
                    return;
                }

            }
            return;
        } 
        forn(i, N) {
            if (!(mask & (1<<i))) {
                if (solve(mask, u) == solve(mask | (1 << i), i) + dist[u][i]) {
                    path.pb(i);
                    buildPath(mask|(1<<i), i);
                    return;
                } 
            }
        }
    }
};
