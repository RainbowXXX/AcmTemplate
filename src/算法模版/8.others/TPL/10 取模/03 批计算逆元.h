/*
线性求n个数a[1]...a[n]的逆元
s[i]前缀积 求s[n]的逆元sv[n]
a[i].inv=s[i-1]*sv[i];
*/
template <ll SZ>
struct InvT
{
	ll sz, mod;
	ll dt[SZ], dt_inv[SZ];
	ll s[SZ], s_inv[SZ];
	void Init(ll sz, ll mod)
	{
		this->sz = sz;
		this->mod = mod;
		s[0] = 1;
		FOR(i, 1, sz)
		s[i] = s[i - 1] * dt[i] % mod;
		// 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
		s_inv[sz] = Pow(s[sz], mod - 2);
		ROF(i, sz, 1)
		s_inv[i - 1] = s_inv[i] * dt[i] % mod;
		FOR(i, 1, sz)
		dt_inv[i] = s_inv[i] * s[i - 1] % mod;
	}
};
InvT<SZ> invT;