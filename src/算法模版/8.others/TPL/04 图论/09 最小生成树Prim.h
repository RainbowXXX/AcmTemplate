template <ll V_SZ>
struct Prim
{
public:
	static constexpr ll ERR = -1;

	ll v_sz;
	VE<PLL> E[V_SZ];

	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		FOR(i, 0, v_sz)
		E[i].clear();
		return;
	}
	void Push(ll bg, ll ed, ll wt) { E[bg].push_back({ed, wt}); }
	ll Build(ll sou)
	{
		FOR(i, 0, v_sz)
		{
			vis[i] = false;
			dis[i] = INF;
		}
		HEAP<Node> q;
		ll res = 0;
		vis[sou] = true;
		dis[sou] = 0;
		ll g_sz = 1;
		for (auto &[id, len] : E[sou])
		{
			q.push({id, len});
			dis[id] = len;
		}
		while (not q.empty())
		{
			auto [id, len] = q.top();
			q.pop();
			if (vis[id])
				continue;
			vis[id] = true;
			++g_sz;
			res += len;
			for (auto &[id2, len2] : E[id])
			{
				if (vis[id2])
					continue;
				if (dis[id2] > len2)
				{
					dis[id2] = len2;
					q.push({id2, len2});
				}
			}
		}
		if (g_sz != v_sz)
			return ERR;
		return res;
	}

protected:
	bool vis[V_SZ];
	ll dis[V_SZ];
	struct Node
	{
		ll id, len;
		bool operator<(const Node &oth) const { return len > oth.len; }
	};
};
Prim<SZ> G;