/*
ST表
EXP:需要满足:2^EXP > SZ
F:可以换成max/min 但不可以换成sum
sz:当前大小
dt[0][1 ~ sz]:初始数据容器
Init(sz):O(1)初始化
Build():O(NlogN)建表
Qry(l,r):O(1)查询F(l ~ r)
*/
template <ll SZ>
struct STT
{
	static constexpr ll EXP = 22;
	ll F(const ll &lh, const ll &rh) const { return std::gcd(lh, rh); }
	ll sz;
	ll dt[EXP + 1][SZ + 1];
	void Init(ll sz) { this->sz = sz; }
	void Build(void)
	{
		FOR(exp, 1, EXP)
		for (ll i = 1; i + (1LL << exp) - 1 <= sz; ++i)
			dt[exp][i] = F(dt[exp - 1][i], dt[exp - 1][i + (1LL << (exp - 1))]);
		return;
	}
	ll Qry(ll l, ll r)
	{
		ll k = std::log2(r - l + 1);
		return F(dt[k][l], dt[k][r - (1LL << k) + 1]);
	}
};
STT<SZ> stt;