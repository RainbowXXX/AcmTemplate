/*
树状数组04
区间修改 区间查询
sz:当前大小
Init(sz):O(N)初始化
Mdf(l,r,d):O(logN)使a[l ~ r]+=d
Qry(l,r):O(logN)查询Sum(l ~ r)
*/
template <ll SZ>
struct BIT
{
public:
	ll sz;
	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 0, 1)
		FOR(j, 0, sz)
		dt[i][j] = 0;
		return;
	}
	void Mdf(ll l, ll r, ll d)
	{
		MdfD(0, l, d);
		MdfD(1, l, d * l);
		MdfD(0, r, -d);
		MdfD(1, r, -d * (r + 1));
		return;
	}
	ll Qry(ll l, ll r) { return QryS(r) - QryS(l - 1); }

protected:
	ll dt[2][SZ + 1];
	ll Lowbit(ll x) { return x & (-x); }
	void MdfD(ll k, ll p, ll d)
	{
		for (ll i = p; i <= sz; i += Lowbit(i))
			dt[k][i] += d;
		return;
	}
	ll QryS(ll p)
	{
		ll res = 0;
		for (ll i = p; i > 0; i -= Lowbit(i))
			res += (p + 1) * dt[0][i] - dt[1][i];
		return res;
	}
};
BIT<SZ> bt;