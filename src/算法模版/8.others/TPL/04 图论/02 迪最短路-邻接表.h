template <ll V_SZ>
struct DIJ
{
public:
	static constexpr ll ERR = -1;
	ll v_sz;
	VE<PLL> E[V_SZ];
	ll dis[V_SZ];
	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		FOR(i, 0, v_sz)
		E[i].clear();
		return;
	}
	void Push(ll bg, ll ed, ll wt) { E[bg].push_back({ed, wt}); }
	void Build(ll s)
	{
		FOR(i, 0, v_sz)
		{
			dis[i] = INF;
			vis[i] = false;
		}
		dis[s] = 0;
		HEAP<PLL, VE<PLL>, std::greater<PLL>> he;
		he.push({0, s});
		while (not he.empty())
		{
			ll now = he.top().se;
			he.pop();
			if (vis[now])
				continue;
			vis[now] = true;
			for (auto &[aim, wt] : E[now])
			{
				if (vis[aim])
					continue;
				if (dis[aim] > dis[now] + wt)
				{
					dis[aim] = dis[now] + wt;
					he.push({dis[aim], aim});
				}
			}
		}
		return;
	}
	ll Qry(ll p)
	{
		if (p < 1 or p > v_sz or dis[p] == INF)
			return ERR;
		return dis[p];
	}

protected:
	bool vis[V_SZ];
};
DIJ<SZ> G;