/*
排列组合
sz:当前大小
fac[i]:i!
fac_inv[i]:1/(i!)
Init(sz):O(N)初始化
A(n,m):n中取m排列数
IA(n,m):1/A(n,m)
C(n,m):n中取m组合数
IC(n,m):1/C(n,m)
*/
template <ll SZ>
struct AC
{
	ll sz;
	mint fac[SZ+1];
	mint fac_inv[SZ+1];
	void Init(ll sz)
	{
		this->sz = sz;
		fac[0] = 1;
		FOR(i, 1, sz)
		fac[i] = fac[i - 1] * i;
		fac_inv[sz] = fac[sz].Inv();
		ROF(i, sz - 1, 0)
		fac_inv[i] = fac_inv[i + 1] * (i + 1);
		return;
	}
	mint A(ll n, ll m)
	{
		if (m > n or m < 0 or n < 0)
			return 0;
		return fac[n] * fac_inv[n - m];
	}
	mint IA(ll n, ll m)
	{
		if (m > n or m < 0 or n < 0)
			return 0;
		return fac_inv[n] * fac[n - m];
	}
	mint C(ll n, ll m)
	{
		if (m > n or m < 0 or n < 0)
			return 0;
		return fac[n] * fac_inv[m] * fac_inv[n - m];
	}
	mint IC(ll n, ll m)
	{
		if (m > n or m < 0 or n < 0)
			return 0;
		return fac_inv[n] * fac[m] * fac[n - m];
	}
};
AC<SZ> ac;