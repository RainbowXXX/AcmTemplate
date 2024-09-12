// 在s中查询所有p的出现位置
template <ll S_SZ, ll P_SZ>
struct KMP
{
	ll ls, lp;
	// from 1
	char s[S_SZ], p[P_SZ];
	ll nxt[P_SZ];
	VE<PLL> res;
	void Init(ll ls, ll lp)
	{
		this->ls = ls;
		this->lp = lp;
		return;
	}
	void Build(void)
	{
		for (ll i = 2, j = 0; i <= lp; ++i)
		{
			while (j and p[i] != p[j + 1])
				j = nxt[j];
			if (p[i] == p[j + 1])
				++j;
			nxt[i] = j;
		}
		return;
	}
	void Qry(void)
	{
		res.clear();
		for (ll i = 1, j = 0; i <= ls; ++i)
		{
			while (j and s[i] != p[j + 1])
				j = nxt[j];
			if (s[i] == p[j + 1])
				++j;
			if (j == lp)
			{
				ll bg = i - lp + 1;
				ll ed = i;
				res.push_back({bg, ed});
				j = nxt[j];
			}
		}
		return;
	}
};
KMP<SZ, SZ> kmp;