/*
Z function: $f_i$ is the max \texttt{len} such that \texttt{s.substr(0,len) == s.substr(i,len)}\\
Complexity: $O(|s|)$
---
Source: https://cp-algorithms.com/string/z-function.html
*/
vi z_function(string s) {
    int n = len(s);
    vi z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if(i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}