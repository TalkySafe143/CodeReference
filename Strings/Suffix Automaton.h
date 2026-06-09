/*
Suffix automaton
---

*/
constexpr int N = 1e5 + 5;

namespace suffix_automata {

constexpr int SIGMA = 11;

struct state
{
  int link, len, l, r; // [l, r) in string position
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
add_char (char c, int i)
{
  int nw = sz++;

  st[nw].len = st[last].len + 1;
  nodes.push_back (nw);

  st[nw].l = st[last].l;
  st[nw].r = st[last].r + 1;

  int p = last;
  int ch = static_cast<int> (c - '0');

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
	  nodes.push_back (clone);

	  st[clone].len = st[p].len + 1;

	  st[clone].l = st[q].r - st[clone].len;
	  st[clone].r = st[q].r;

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

