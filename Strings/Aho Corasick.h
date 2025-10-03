/*
Aho-Corasick automata implementation - BFS based construction
Complexity for \textbf{Build}: $O(|Patterns|)$ and \textbf{Search patterns}:
$O(|Text| + |Matches|)$. How to: \begin{itemize} \item Init with $v = 0$ in the
main program. \item Run $v = go(v, c)$ where $c$ is the letter to move. \item
Run \texttt{outputChain(v, lambda(vertex founded))} to print the chain, in the
lambda will be the trie vertex found. \end{itemize}
---
Sources: Own & CP Algorithms
- https://cp-algorithms.com/string/aho_corasick.html
Verification: https://vjudge.net/problem/UVA-10679
*/

template <int K> struct AhoCorasick {
  struct Node {
    int link = 0,     // suffix link
        out_link = 0; // output link
    vector<int> next = vector<int>(K, 0), out;
    vector<int> go = vector<int>(K, -1);
  };
  int n = 1, p = 0;
  vector<Node> trie = vector<Node>(1);

  int alloc_node() {
    trie.emplace_back();
    return n++;
  }

  inline int get(char c) {
    /*
     using A-Za-z letters
          if (c >= 'a') return ('Z' - 'A') + (c - 'a') + 1;
          return c - 'A';
     */
    return c - 'a';
  }

  int add_string(string &T) {
    int u = 0;
    for (auto c : T) {
      if (not trie[u].next[get(c)])
        trie[u].next[get(c)] = alloc_node();
      u = trie[u].next[get(c)];
    }
    trie[u].out.push_back(p);
    return p++;
  }

  void build() {
    queue<int> q;
    q.push(0);
    while (not q.empty()) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < K; c++) {
        int v = trie[u].next[c];
        if (not v)
          trie[u].next[c] = trie[trie[u].link].next[c];
        else {
          trie[v].link = u ? trie[trie[u].link].next[c] : 0;
          trie[v].out_link = trie[trie[v].link].out.empty()
                                 ? trie[trie[v].link].out_link
                                 : trie[v].link;
          q.push(v);
        }
      }
    }
  }

  void output_chain(int v, function<void(int)> visit) {
    if (not trie[v].out.empty())
      visit(v);
    if (trie[v].out_link)
      output_chain(trie[v].out_link, visit);
  }

  int go(int v, char ch) {
    int c = get(ch);
    if (trie[v].go[c] == -1) {
      if (not trie[v].next[c])
        trie[v].go[c] = (v == 0) ? 0 : go(trie[v].link, ch);
      else
        trie[v].go[c] = trie[v].next[c];
    }

    return trie[v].go[c];
  }
};
