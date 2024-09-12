/*
树状数组01
单点修改 前缀查询
sz:当前大小
Init(sz):O(N)初始化
Mdf(p,d):O(logN)使a[p]+=d
Qry(p):O(logN)查询Sum(1 ~ p)
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
	void Mdf(ll p, ll d)
	{
		for (ll i = p; i <= sz; i += Lowbit(i))
			dt[i] += d;
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
};
BIT<SZ> bt;