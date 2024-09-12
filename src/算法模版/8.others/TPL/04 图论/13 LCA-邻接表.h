template <ll V_SZ>
struct LCA
{
public:
	static constexpr ll NUL = -1;
	static constexpr ll EXP = 22 + 1;

	ll v_sz;
	VE<ll> E[V_SZ];
	ll dep[V_SZ];
	ll fa[EXP][V_SZ];

	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		FOR(i, 0, v_sz)
		E[i].clear();
		return;
	}
	void PushE(ll bg, ll ed) { E[bg].push_back(ed); }
	void Build(ll rt)
	{
		dep[rt] = 1;
		DFS(rt, NUL);
		return;
	}
	ll QryLCA(ll v1, ll v2)
	{
		if (dep[v1] < dep[v2])
			swap(v1, v2);
		ll d_dep = dep[v1] - dep[v2];
		FOR(i, 0, EXP - 1)
		if ((d_dep >> i) & 1)
			v1 = fa[i][v1];
		if (v1 == v2)
			return v1;
		ROF(i, EXP - 1, 0)
		{
			if (fa[i][v1] == fa[i][v2])
				continue;
			v1 = fa[i][v1];
			v2 = fa[i][v2];
		}
		return fa[0][v1];
	}

protected:
	void DFS(ll x, ll f)
	{
		fa[0][x] = f;
		FOR(i, 1, EXP - 1)
		fa[i][x] = fa[i - 1][fa[i - 1][x]];
		for (auto &aim : E[x])
		{
			if (aim == x or aim == f)
				continue;
			dep[aim] = dep[x] + 1;
			DFS(aim, x);
		}
		return;
	}
};
LCA<SZ> G;