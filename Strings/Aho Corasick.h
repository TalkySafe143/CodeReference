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

const int K = 55;

struct AhoCorasick {

  struct Vertex {
    int next[K];
    bool output = false;
    string outputStr;

    int p = -1;
    char pch;

    int link = -1; // Suffix link
    int exit = -1; // Output link
    int go[K];

    Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
      fill(begin(next), end(next), -1);
      fill(begin(go), end(go), -1);
    };
  };

  vector<Vertex> trie = vector<Vertex>(1);

  AhoCorasick(vector<string> &p) {
    for (auto &d : p)
      add_string(d);
    buildLinks();
  }

  void buildLinks() {
    queue<int> r, q;
    forn(i, K) {
      if (trie[0].next[i] != -1) {
        trie[trie[0].next[i]].link = 0;
        r.push(trie[0].next[i]);
      }
    }

    while (len(r)) {
      int u = r.front();
      r.pop();
      forn(i, K) {
        if (trie[u].next[i] != -1) {
          q.push(trie[u].next[i]);
        }
      }
    }

    while (len(q)) {
      int wa = q.front();
      q.pop();
      int x = trie[trie[wa].p].link;
      while (true) {
        char ch = trie[wa].pch;
        // if (ch >= 97) ch = (ch-'a') + 91; // If u use A-Za-z letters
        int c = ch - 'A';
        if (trie[x].next[c] != -1) {
          trie[wa].link = trie[x].next[c];
          break;
        }

        if (x == 0) {
          trie[wa].link = 0;
          break;
        }
        x = trie[x].link;
      }

      int u = trie[wa].link;
      if (trie[u].output)
        trie[wa].exit = u;
      else
        trie[wa].exit = trie[u].exit;

      forn(i, K) if (trie[wa].next[i] != -1) q.push(trie[wa].next[i]);
    }
  }

  void add_string(string &a) {
    int v = 0;
    for (char ch : a) {
      //      if (ch >= 97) ch = (ch-'a') + 91; // If u use A-Za-z letters
      int c = ch - 'A'; // Change depending capital letters or not
      if (trie[v].next[c] == -1) {
        trie[v].next[c] = trie.size(); // next apuntará al nodo del trie (v)
        trie.emplace_back(v, ch);      // Se construye con el parent como v
      }

      v = trie[v].next[c];
    }

    trie[v].output = true;
    trie[v].outputStr = a;
  }

  void outputChain(int v, function<void(int)> visit) {
    if (trie[v].output)
      visit(v);
    if (trie[v].exit != -1)
      outputChain(trie[v].exit, visit);
  }

  int go(int v, char ch) {
    // if (ch >= 97) ch = (ch-'a') + 91; // If u use A-Za-z letters
    int c = ch - 'A';
    if (trie[v].go[c] == -1) {
      if (trie[v].next[c] != -1)
        trie[v].go[c] = trie[v].next[c];
      else
        trie[v].go[c] = v == 0 ? 0 : go(trie[v].link, ch);
    }

    return trie[v].go[c];
  }
};
