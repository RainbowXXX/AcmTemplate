template <typename NODE, ll SZ>
struct SGT
{
#define LS (id << 1)
#define RS (id << 1 | 1)
public:
	ll sz;
	void Init(ll sz)
	{
		this->sz = sz;
		Build(1, 1, sz);
		return;
	}
	void Mdf(ll l, ll r, ll v) { Mdf(l, r, v, 1, 1, sz); }
	NODE Qry(ll l, ll r) { return Qry(l, r, 1, 1, sz); }

protected:
	NODE nd[SZ << 2 | 1];
	void Build(ll id, ll id_l, ll id_r)
	{
		if (id_l == id_r)
		{
			nd[id].Init(id_l);
			return;
		}
		ll id_m = (id_l + id_r) >> 1;
		Build(LS, id_l, id_m);
		Build(RS, id_m + 1, id_r);
		nd[id].PushUp(nd[LS], nd[RS]);
		return;
	}
	void Mdf(ll l, ll r, ll v, ll id, ll id_l, ll id_r)
	{
		if (l <= id_l and id_r <= r)
		{
			nd[id].Mdf(id_l, id_r, v);
			return;
		}
		nd[id].PushDown(id_l, id_r, nd[LS], nd[RS]);
		ll md = (id_l + id_r) >> 1;
		if (l <= md)
			Mdf(l, r, v, LS, id_l, md);
		if (md < r)
			Mdf(l, r, v, RS, md + 1, id_r);
		nd[id].PushUp(nd[LS], nd[RS]);
		return;
	}
	NODE Qry(ll l, ll r, ll id, ll id_l, ll id_r)
	{
		if (l <= id_l and id_r <= r)
			return nd[id];
		nd[id].PushDown(id_l, id_r, nd[LS], nd[RS]);
		NODE res;
		ll md = (id_l + id_r) >> 1;
		if (l <= md and md < r)
			res.PushUp(Qry(l, r, LS, id_l, md), Qry(l, r, RS, md + 1, id_r));
		else if (l <= md)
			return Qry(l, r, LS, id_l, md);
		else if (md < r)
			return Qry(l, r, RS, md + 1, id_r);
		return res;
	}
#undef LS
#undef RS
};

struct SUM_MDF_NODE
{
	static constexpr ll NUL = 0;
	ll sum;
	ll lz;
	void Init(ll p)
	{
		sum = 0;
		lz = NUL;
		return;
	}
	void PushUp(const SUM_MDF_NODE &ls, const SUM_MDF_NODE &rs)
	{
		sum = ls.sum + rs.sum;
		lz = NUL;
		return;
	}
	void PushDown(ll id_l, ll id_r, SUM_MDF_NODE &ls, SUM_MDF_NODE &rs)
	{
		if (lz == NUL)
			return;
		ll id_m = (id_l + id_r) >> 1;
		ls.Mdf(id_l, id_m, lz);
		rs.Mdf(id_m + 1, id_r, lz);
		lz = NUL;
		return;
	}
	void Mdf(ll id_l, ll id_r, ll v)
	{
		sum += (id_r - id_l + 1) * v;
		lz += v;
		return;
	}
};
struct SUM_COV_NODE
{
	static constexpr ll NUL = -114514;
	ll sum;
	ll lz;
	void Init(ll p)
	{
		sum = 0;
		lz = NUL;
		return;
	}
	void PushUp(const SUM_COV_NODE &ls, const SUM_COV_NODE &rs)
	{
		sum = ls.sum + rs.sum;
		lz = NUL;
		return;
	}
	void PushDown(ll id_l, ll id_r, SUM_COV_NODE &ls, SUM_COV_NODE &rs)
	{
		if (lz == NUL)
			return;
		ll id_m = (id_l + id_r) >> 1;
		ls.Mdf(id_l, id_m, lz);
		rs.Mdf(id_m + 1, id_r, lz);
		lz = NUL;
		return;
	}
	void Mdf(ll id_l, ll id_r, ll v)
	{
		sum = (id_r - id_l + 1) * v;
		lz = v;
		return;
	}
};
struct MAX_MDF_NODE
{
	static constexpr ll NUL = 0;
	ll mx;
	ll lz;
	void Init(ll p)
	{
		mx = -INF;
		lz = NUL;
		return;
	}
	void PushUp(const MAX_MDF_NODE &ls, const MAX_MDF_NODE &rs)
	{
		mx = std::max(ls.mx, rs.mx);
		lz = NUL;
		return;
	}
	void PushDown(ll id_l, ll id_r, MAX_MDF_NODE &ls, MAX_MDF_NODE &rs)
	{
		if (lz == NUL)
			return;
		ll id_m = (id_l + id_r) >> 1;
		ls.Mdf(id_l, id_m, lz);
		rs.Mdf(id_m + 1, id_r, lz);
		lz = NUL;
		return;
	}
	void Mdf(ll id_l, ll id_r, ll v)
	{
		mx += v;
		lz += v;
		return;
	}
};
struct MAX_COV_NODE
{
	static constexpr ll NUL = -114514;
	ll mx;
	ll lz;
	void Init(ll p)
	{
		mx = -INF;
		lz = NUL;
		return;
	}
	void PushUp(const MAX_COV_NODE &ls, const MAX_COV_NODE &rs)
	{
		mx = std::max(ls.mx, rs.mx);
		lz = NUL;
		return;
	}
	void PushDown(ll id_l, ll id_r, MAX_COV_NODE &ls, MAX_COV_NODE &rs)
	{
		if (lz == NUL)
			return;
		ll id_m = (id_l + id_r) >> 1;
		ls.Mdf(id_l, id_m, lz);
		rs.Mdf(id_m + 1, id_r, lz);
		lz = NUL;
		return;
	}
	void Mdf(ll id_l, ll id_r, ll v)
	{
		mx = v;
		lz = v;
		return;
	}
};

// SGT<SUM_MDF_NODE, SZ> sgt;
// SGT<SUM_COV_NODE, SZ> sgt;
// SGT<MAX_MDF_NODE, SZ> sgt;
// SGT<MAX_COV_NODE, SZ> sgt;