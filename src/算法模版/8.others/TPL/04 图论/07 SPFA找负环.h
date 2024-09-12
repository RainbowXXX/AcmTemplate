// 有负边但是没有负环的最短路
template <ll V_SZ>
struct SPFA
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
	void PushE(ll bg, ll ed, ll wt) { E[bg].push_back({ed, wt}); }
	// return 是否存在负环
	bool Build(ll s)
	{
		FOR(i, 0, v_sz)
		{
			dis[i] = INF;
			vis[i] = false;
			cnt[i] = 0;
		}
		dis[s] = 0;
		vis[s] = true;
		queue<ll> q;
		q.push(s);
		while (not q.empty())
		{
			ll now = q.front();
			q.pop();
			vis[now] = false;
			for (auto &[aim, wt] : E[now])
				if (dis[aim] > dis[now] + wt)
				{
					dis[aim] = dis[now] + wt;
					if (not vis[aim])
					{
						q.push(aim);
						vis[aim] = true;
						++cnt[aim];
						if (cnt[aim] >= v_sz)
							return true;
					}
				}
		}
		return false;
	}
	ll Qry(ll p)
	{
		if (p < 1 or p > v_sz or dis[p] == INF)
			return ERR;
		return dis[p];
	}

protected:
	bool vis[V_SZ];
	ll cnt[V_SZ];
};
SPFA<SZ> G;