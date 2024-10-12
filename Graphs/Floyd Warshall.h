/*
Computes shortest path for every pair of nodes.\\
Complexity: $O(|V|^3)$.
*/
struct Floyd {

    const ll INF = 1e18;
    vector<vl> dist;

    Floyd(vector<vpl> &adj, int n) {
        dist.assign(n+5, vl(n+5, INF));
        forn(i, n) {
            dist[i+1][i+1]=0;
            for (auto [v, len]: adj[i+1]) dist[i+1][v]=len;
        }

        foran(z,1,n+1) {
            foran(i,1,n+1) {
                foran(j,1,n+1) {
                    // if (d[i][k] < INF && d[k][j] < INF) // if negative cycles
                    dist[i][j] = min(dist[i][j], dist[i][z]+dist[z][j]);
                }
            }
        }
    }

};