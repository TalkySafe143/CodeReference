/*
Suffix automaton
---

*/
constexpr int N = 1e5 + 5;

namespace suffix_automata {

constexpr int SIGMA = 26;

struct state
{
  int link, len;
  vector<int> go = vector<int> (SIGMA, 0);
};

state st[N << 1];
int last, sz;

void
init () // just inits the root
{
  st[0].link = -1;
  st[0].len = 0;
  sz++;
  last = 0;
}

void
add_char (char c)
{
  int nw = sz++;
  st[nw].len = st[last].len + 1;
  int p = last;
  int ch = static_cast<int> (c - 'a');

  while (p != -1 and not st[p].go[ch])
    {
      st[p].go[ch] = nw;
      p = st[p].link;
    }

  if (p == -1)
    {
      st[nw].link = 0;
    }
  else
    {
      int q = st[p].go[ch];
      if (st[q].len == st[p].len + 1)
	{
	  st[nw].link = q;
	}
      else
	{
	  int clone = sz++;
	  st[clone].len = st[p].len + 1;
	  st[clone].link = st[q].link;
	  st[clone].go = st[q].go;

	  while (p != -1 and st[p].go[ch] == q)
	    {
	      st[p].go[ch] = clone;
	      p = st[p].link;
	    }

	  st[q].link = st[nw].link = clone;
	}
    }
  last = nw;
}

}; // namespace suffix_automata


