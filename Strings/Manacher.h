/*
Given string $s$ with length $n$. Find all the pairs $(i, j)$ such that substring $s[i\dots j]$ is a palindrome.\\
Complexity: $O(|s|)$, returns vector $p$, where $p_i$ is the number of palindromes starting in $i$. Where $i$ is the center.
---
Source: https://cp-algorithms.com/string/manacher.html
*/

vi manacher_odd(string s) {
    int n = len(s);
    s = "$" + s + "^";
    vi p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vi(begin(p) + 1, end(p) - 1);
}

vi manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vi(begin(res) + 1, end(res) - 1);
}