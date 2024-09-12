template <ll V_SZ>
struct TuoPu
{
	ll v_sz;
	VE<ll> E[V_SZ];
	ll in_du[V_SZ];
	VE<ll> res;

	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		FOR(i, 0, v_sz)
		E[i].clear();
		FOR(i, 0, v_sz)
		in_du[i] = 0;
		res.clear();
		return;
	}
	void PushE(ll bg, ll ed)
	{
		E[bg].push_back(ed);
		++in_du[ed];
		return;
	}
	bool Build(void)
	{
		res.clear();

		queue<ll> q;
		FOR(i, 1, v_sz)
		if (in_du[i] == 0)
			q.push(i);

		while (not q.empty())
		{
			ll now = q.front();
			q.pop();
			res.push_back(now);
			for (auto &son : E[now])
			{
				--in_du[son];
				if (in_du[son] == 0)
					q.push(son);
			}
		}

		if (res.size() == v_sz)
			return true;
		return false;
	}
};
TuoPu<SZ> G;