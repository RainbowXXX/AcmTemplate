/*
哈希表
快速比较子串是否相等
BASE:进制 MOD:模数 SZ:上限
ERR:报错值
sz:当前大小
s:初始字符串容器
Init(sz):O(N)初始化
Build():O(N)建表
Qry(l,r):O(1)查询s[l ~ r]的哈希值
常用BASE-MOD:
233 1004535809
239 2013265921
常用MOD:
998244389, 998244391, 998244397, 998244353, 1e9+7
*/
template <ll BASE, ll MOD, ll SZ>
struct Hash
{
public:
	static constexpr ll ERR = -1;
	ll sz;
	char s[SZ + 1];
	void Init(ll sz)
	{
		this->sz = sz;
		p[0] = 1;
		FOR(i, 1, sz)
		p[i] = p[i - 1] * BASE % MOD;
		return;
	}
	void Build(void)
	{
		hs[0] = hsr[0] = 0;
		FOR(i, 1, sz)
		{
			hs[i] = hs[i - 1] * BASE % MOD + s[i], hs[i] %= MOD;
			hsr[i] = hsr[i - 1] * BASE % MOD + s[sz + 1 - i], hsr[i] %= MOD;
		}
		return;
	}
	ll Qry(ll l, ll r)
	{
		if (r < l)
			return ERR;
		if (l < 1 or sz < r)
			return ERR;
		return (hs[r] - hs[l - 1] * p[r - l + 1] % MOD + MOD) % MOD;
	}
	ll QryR(ll L, ll R)
	{
		if (R < L)
			return ERR;
		if (L < 1 or sz < R)
			return ERR;
		ll l = sz + 1 - R;
		ll r = sz + 1 - L;
		return (hsr[r] - hsr[l - 1] * p[r - l + 1] % MOD + MOD) % MOD;
	}

protected:
	ll p[SZ + 1];
	ll hs[SZ + 1], hsr[SZ + 1];
};
constexpr ll BASE1 = 233, MOD1 = 1004535809;
constexpr ll BASE2 = 239, MOD2 = 2013265921;
Hash<BASE1, MOD1, SZ> h1;
Hash<BASE2, MOD2, SZ> h2;