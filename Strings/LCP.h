/**
    LCP array

    Source: Me

    Verification: *
    Complexity: O(|S|log |S|) for Suffix Array computation
                O(|S|) for the LCP computation.

    Need SuffixArray.h
*/

struct LCP {

    vi lcpAr;

    LCP(string &S, SuffixArray order) {
        vi pos;
        lcpAr.assign(len(S)-1, 0);
        int lcp = 0;
        invertSuffixArray(order, pos);
        int suffix = order[0];
        forn(i, len(S)-1) {
            int orderIndex = pos[suffix];
            if (orderIndex == len(S)-1) {
                lcp = 0;
                suffix = (suffix+1)%len(S);
                continue;
            }
            int nextSuffix = order[orderIndex+1];
            lcp = lcpSuffixes(S, suffix, nextSuffix, lcp-1);
            lcpAr[orderIndex] = lcp;
            suffix = (suffix+1)%len(S);
        }
    }

    // Compute LCP from scracth
    int lcpSuffixes(string &S, int i, int j, int equal) {
        int lcp = max(0, equal);
        while (i + lcp < len(S) && j + lcp < len(S)){
            if (S[i+lcp] == S[j+lcp]) lcp++;
            else break;
        }
        return lcp;
    }

    // Invert SuffixArray to compute the next suffix in the array
    void invertSuffixArray(SuffixArray order, vi& pos) {
        pos.assign(len(order), 0);
        forn(i, n) pos[order[i]] = i;
    }
};
