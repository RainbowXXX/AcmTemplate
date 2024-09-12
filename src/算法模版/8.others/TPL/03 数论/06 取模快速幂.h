// O(logN)计算base ^ exp (Mod mod)
using i128 = __int128;
ll Pow(ll base, ll exp, ll mod)
{
	assert(exp >= 0);
	ll res = 1;
	base = (base % mod + mod) % mod;
	while (exp)
	{
		if (exp & 1)
			res = (i128)res * base % mod;
		base = (i128)base * base % mod;
		exp >>= 1;
	}
	return res;
}