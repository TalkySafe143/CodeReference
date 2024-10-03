/*
Burrows–Wheeler Transform
Complexity for \textbf{Build}: $O(|Text|^2)$ and for \textbf{Search patterns}: $O(|Text|)$.
How to:
\begin{itemize}
\item Use the constructor to search patterns, first you have to build BTW before call patternMatching.
\item You can use the other methods separately.
\item Remember to add a \$.
\end{itemize}
---
Sources: me
Verification: Coursera assignment
*/

struct BWT {

    string btw, firstCol;
    vector<vi> cntPrefix;
    vi firstOcurrence;

    BWT(string s, bool isBtw) {
        if (isBtw) btw = s;
        else btw = transform(s);
        getFirstCol(btw, firstCol, firstOcurrence);
        getPrefixCount(btw, cntPrefix);
    }

    BWT() {};

    string transform(string s) {
        vector<string> M;
        string bwt;
        char start = s.back();
        M.pb(s);
        s = s.back() + s.substr(0, len(s)-1);
        while (s.back() != start) {
            M.pb(s);
            s = s.back() + s.substr(0, len(s)-1);
        }
        sort(all(M));
        for (auto d: M) bwt += d.back();
        return bwt;
    }

    void getPrefixCount(string &lastCol, vector<vi> &cnt) {
        cnt.assign(30, vi(len(lastCol)+1, 0));
        forn(i, 30) {
            char c;
            if (i == 0) c = '$';
            else c = 'A'+i-1;
            forn(j, len(lastCol)) cnt[i][j+1] = cnt[i][j] + (lastCol[j] == c);
        }
    }

    void getFirstCol(string &transform, string &col, vi &firstOcurrence) {
        vi cnt;
        cnt.assign(30, 0); firstOcurrence.assign(30, -1);
        for (auto c: transform) {
            if (c == '$') cnt[0]++;
            else cnt[c-'A'+1]++;
        }
        forn(i, 30) {
            if (cnt[i] > 0) firstOcurrence[i] = len(col);
            forn(j, cnt[i]) {
                if (i == 0) col += '$';
                else col += ('A'+i-1);
            }
        }
    }


    string reconstruct(string &transform) {
        vi mappedIdx(len(transform)), firstOcurrence;
        string col;

        getFirstCol(transform, col, firstOcurrence);

        vi cntV;
        cntV.assign(30, 0);
        forn(i, len(transform)) {
            int c;
            if (transform[i] == '$') c = 0;
            else c = transform[i]-'A'+1;
            mappedIdx[i] = firstOcurrence[c]+cntV[c];
            cntV[c]++;
        }
        int curr = 0;
        string ans; ans += col[0];
        while (mappedIdx[curr] != 0) {
            ans += transform[curr];
            curr = mappedIdx[curr];
        }

        reverse(all(ans));
        return ans;
    }

    int patternMatching(string &p) {
        int top = 0, bottom = len(btw)-1, pIdx = len(p)-1;
        while (top <= bottom) {
            if (pIdx >= 0) {
                char sym = p[pIdx]-'A'+1;
                pIdx--;
                if (cntPrefix[sym][bottom+1]-cntPrefix[sym][top] > 0) {
                    top = firstOcurrence[sym] + cntPrefix[sym][top];
                    bottom = firstOcurrence[sym] + cntPrefix[sym][bottom+1]-1;
                } else return 0;

            } else return bottom - top + 1 ;
        }
        return 0;
    }
};
