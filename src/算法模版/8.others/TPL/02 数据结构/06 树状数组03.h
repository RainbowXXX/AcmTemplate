/*
树状数组03
区间修改 单点查询
sz:当前大小
Init(sz):O(N)初始化
Mdf(l,r,d):O(logN)使a[l ~ r]+=d
Qry(p):O(logN)查询a[p]
*/
template <ll SZ>
struct BIT
{
public:
	ll sz;
	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 0, sz)
		dt[i] = 0;
		return;
	}
	void Mdf(ll l, ll r, ll d)
	{
		MdfD(l, d);
		MdfD(r + 1, -d);
		return;
	}
	ll Qry(ll p)
	{
		ll res = 0;
		for (ll i = p; i > 0; i -= Lowbit(i))
			res += dt[i];
		return res;
	}

protected:
	ll dt[SZ + 1];
	ll Lowbit(ll x) { return x & (-x); }
	void MdfD(ll p, ll d)
	{
		for (ll i = p; i <= sz; i += Lowbit(i))
			dt[i] += d;
		return;
	}
};
BIT<SZ> bt;