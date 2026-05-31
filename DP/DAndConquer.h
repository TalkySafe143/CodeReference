/*
Divide and conquer optimization DP. $O(nm\log n)$ in this case. Remember
Try to compute the cost function, you need the last row computed.
---
Source: me
*/

void
solve (int l, int r, int opt_l, int opt_r, int k)
{
  if (l + 1 >= r)
    return;

  int mid = midpoint (l, r);
  int opt = -1;

  for (int i = opt_l; i <= min (mid, opt_r); i++)
    {
      if (dp[mid][k] > dp[i][k - 1] + C (i + 1, mid))
	{
	  dp[mid][k] = dp[i][k - 1] + C (i + 1, mid);
	  opt = i;
	}
    }

  solve (l, mid, opt_l, opt, k);
  solve (mid, r, opt, opt_r, k);
}
