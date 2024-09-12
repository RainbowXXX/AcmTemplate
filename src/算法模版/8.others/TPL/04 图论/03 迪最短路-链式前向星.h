// 双向边要*2
template <ll V_SZ, ll E_SZ>
struct DIJ
{
public:
	static constexpr ll NUL = -1;
	static constexpr ll ERR = -1;
	ll v_sz, e_sz;
	ll v_hd[V_SZ];
	ll e_ed[E_SZ];
	ll e_wt[E_SZ];
	ll e_nxt[E_SZ];
	ll dis[V_SZ];
	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		e_sz = 0;
		FOR(i, 0, v_sz)
		v_hd[i] = NUL;
		return;
	}
	void Push(ll bg, ll ed, ll wt)
	{
		++e_sz;
		e_ed[e_sz] = ed;
		e_wt[e_sz] = wt;
		e_nxt[e_sz] = v_hd[bg];
		v_hd[bg] = e_sz;
		return;
	}
	void Build(ll s)
	{
		FOR(i, 0, v_sz)
		{
			dis[i] = INF;
			vis[i] = false;
		}
		dis[s] = 0;
		HEAP<PLL, VE<PLL>, greater<PLL>> he;
		he.push({0, s});
		while (not he.empty())
		{
			ll now = he.top().SE;
			he.pop();
			if (vis[now])
				continue;
			vis[now] = true;
			for (ll i = v_hd[now]; i != NUL; i = e_nxt[i])
			{
				ll aim = e_ed[i];
				if (vis[aim])
					continue;
				if (dis[aim] > dis[now] + e_wt[i])
				{
					dis[aim] = dis[now] + e_wt[i];
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
DIJ<SZ, SZ> G;