template <ll SZ>
struct DSU
{
public:
	ll sz;

	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 0, sz)
		{
			fa[i] = i;
			siz[i] = 1;
		}
		return;
	}
	ll Find(ll m)
	{
		while (m != fa[m])
			m = fa[m] = fa[fa[m]];
		return m;
	}
	bool Same(ll s, ll m) { return Find(s) == Find(m); }
	bool Merge(ll s, ll m)
	{
		s = Find(s);
		m = Find(m);
		if (s == m)
			return false;
		siz[s] += siz[m];
		fa[m] = s;
		return true;
	}
	ll Size(ll s) { return siz[Find(s)]; }

protected:
	ll fa[SZ];
	ll siz[SZ];
};
template <ll V_SZ, ll E_SZ>
struct Kruskal
{
	static constexpr ll ERR = -1;

	ll v_sz, e_sz;
	struct Edge
	{
		ll u, v, wt;
		bool operator<(const Edge &oth) const { return wt < oth.wt; }
	};
	Edge E[E_SZ];
	DSU<V_SZ> dsu;

	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		this->e_sz = 0;
		dsu.Init(v_sz);
		return;
	}
	void Push(ll bg, ll ed, ll wt) { E[++e_sz] = (Edge){bg, ed, wt}; }
	ll Build(void)
	{
		ll res = 0;
		ll cnt = 0;
		std::sort(E + 1, E + e_sz + 1);
		FOR(i, 1, e_sz)
		{
			auto &[u, v, wt] = E[i];
			if (dsu.Merge(u, v))
			{
				res += wt;
				++cnt;
			}
			if (cnt >= v_sz - 1)
				break;
		}
		if (dsu.Size(1) != v_sz)
			return ERR;
		return res;
	}
};
Kruskal<SZ, SZ> G;