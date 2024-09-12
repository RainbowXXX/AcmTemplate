// ABC294G
template <ll SZ>
struct BIT
{
#define LOWBIT(x) ((x) & (-x))

public:
	ll sz;

	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 1, sz)
		dt[i] = 0;
		return;
	}
	void MdfD(ll p, ll d)
	{
		for (ll i = p; i <= sz; i += LOWBIT(i))
			dt[i] += d;
		return;
	}
	void SegMdfA(ll l, ll r, ll d)
	{
		MdfD(l, d);
		MdfD(r + 1, -d);
		return;
	}
	ll QryA(ll p)
	{
		ll res = 0;
		for (ll i = p; i > 0; i -= LOWBIT(i))
			res += dt[i];
		return res;
	}

protected:
	ll dt[SZ];
};
template <ll V_SZ, ll E_SZ>
struct Tree
{
public:
	static constexpr ll NUL = -1;
	static constexpr ll EXP = 21 + 1;
	
	ll v_sz, e_sz;
	ll v_hd[V_SZ];
	struct Edge
	{
		ll ed, wt, nxt, id;
	};
	Edge E[E_SZ];
	ll e_wt[E_SZ];
	ll dep[V_SZ];
	ll fa[EXP][V_SZ];
	ll time_in[V_SZ];
	ll time_out[V_SZ];
	ll e_f[E_SZ];
	BIT<V_SZ> bt;

	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		e_sz = 0;
		FOR(i, 0, v_sz)
		v_hd[i] = NUL;
		return;
	}
	void PushE(ll bg, ll ed, ll wt, ll id)
	{
		E[++e_sz] = (Edge){ed, wt, v_hd[bg], id};
		this->v_hd[bg] = e_sz;
		e_wt[id] = wt;
		return;
	}
	void Build(ll rt)
	{
		dep[rt] = 1;
		timer = 0;
		DFS(rt, NUL);
		bt.Init(v_sz);
		FOR(i, 1, v_sz - 1)
		bt.SegMdfA(time_in[e_f[i]], time_out[e_f[i]], e_wt[i]);
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
	void Upd(ll e_id, ll wt)
	{
		bt.SegMdfA(time_in[e_f[e_id]], time_out[e_f[e_id]], wt - e_wt[e_id]);
		e_wt[e_id] = wt;
		return;
	}
	ll QryDist(ll v1, ll v2) { return bt.QryA(time_in[v1]) + bt.QryA(time_in[v2]) - 2LL * bt.QryA(time_in[QryLCA(v1, v2)]); }

protected:
	ll timer;
	void DFS(ll x, ll fa)
	{
		++timer;
		time_in[x] = timer;
		this->fa[0][x] = fa;
		FOR(i, 1, EXP - 1)
		this->fa[i][x] = this->fa[i - 1][this->fa[i - 1][x]];
		for (ll e_id = v_hd[x]; e_id != NUL; e_id = E[e_id].nxt)
		{
			ll ed = E[e_id].ed;
			if (ed == x or ed == fa)
				continue;
			dep[ed] = dep[x] + 1;
			DFS(ed, x);
			e_f[E[e_id].id] = ed;
		}
		time_out[x] = timer;
		return;
	}
};
Tree<SZ, SZ> tree;

void Solve(void)
{
	ll n;
	cin >> n;
	tree.Init(n);
	FOR(i, 1, n - 1)
	{
		ll u, v, w;
		cin >> u >> v >> w;
		tree.PushE(u, v, w, i);
		tree.PushE(v, u, w, i);
	}
	tree.Build(1);
	ll q;
	cin >> q;
	while (q--)
	{
		ll op, x, y;
		cin >> op >> x >> y;
		if (op == 1)
			tree.Upd(x, y);
		else
			cout << tree.QryDist(x, y) << EDL;
	}
	return;
}