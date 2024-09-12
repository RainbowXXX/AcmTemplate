/*
逆元表
O(N)批计算逆元
sz:当前大小
mod:当前模数 要求是质数
inv[i]:i的逆元
Init(sz,mod):O(N)批计算前sz个数在mod下的逆元
*/
template <ll SZ>
struct InvT
{
	ll sz, mod;
	ll inv[SZ + 1];
	void Init(ll sz, ll mod)
	{
		this->sz = sz;
		this->mod = mod;
		inv[0] = 0;
		inv[1] = 1;
		FOR(i, 2, sz)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		return;
	}
};
InvT<SZ> invT;