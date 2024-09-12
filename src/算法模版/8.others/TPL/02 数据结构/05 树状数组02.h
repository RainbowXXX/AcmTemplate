/*
	树状数组02
	单点覆盖 前缀查询
	NUL:空值 F=max时NUL=-INF F=min时NUL=INF
	F(lh,rh):可以是max/min
	sz:当前大小
	Init(sz):O(N)初始化
	Cov(p,v):O(logN)使a[p]=v
	Qry(p):O(logN)查询F(1 ~ p)
*/
template <ll SZ>
struct BIT
{
public:
	static constexpr ll NUL = -INF;
	ll F(const ll &lh, const ll &rh) const { return std::max(lh, rh); }
	ll sz;
	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 0, sz)
		dt[i] = NUL;
		return;
	}
	void Cov(ll p, ll v)
	{
		for (ll i = p; i <= sz; i += Lowbit(i))
			dt[i] = F(dt[i], v);
		return;
	}
	ll Qry(ll p)
	{
		ll res = NUL;
		for (ll i = p; i > 0; i -= Lowbit(i))
			res = F(res, dt[i]);
		return res;
	}

protected:
	ll dt[SZ + 1];
	ll Lowbit(ll x) { return x & (-x); }
};
BIT<SZ> bt;