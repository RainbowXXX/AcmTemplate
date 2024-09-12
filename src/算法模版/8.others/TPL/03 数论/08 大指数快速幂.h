template <ll SZ, ll MOD>
struct BigExpPowTool
{
public:
	ll sz;
	char exp_s[SZ];
	void Init(ll sz) { this->sz = sz; }
	ll BigExpPow(ll base)
	{
		ll sz = this->sz;
		if (sz == 1 and exp_s[1] == '0')
			return 1;
		if (base == 0)
			return 0;
		ll res = 1;
		while (sz)
		{
			if (exp_s[sz] != '0')
			{
				ll tmp = exp_s[sz] - '0';
				res *= Pow(base, tmp, MOD);
				res %= MOD;
			}
			base = Pow(base, 10, MOD);
			--sz;
		}
		return res;
	}

protected:
	ll Pow(ll base, ll exp, ll mod)
	{
		assert(exp >= 0);
		ll res = 1;
		base %= mod;
		while (exp)
		{
			if (exp & 1)
				res = (res * base) % mod;
			base = (base * base) % mod;
			exp >>= 1;
		}
		return res;
	}
};
BigExpPowTool<SZ, MOD> tmp;