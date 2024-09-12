/*
复杂度：
判x是否素数 复杂度为O(k * log^3(n))，其中k是算法中进行的随机性测试的次数，n是待判断的数的位数。
分解x 复杂度为x的1/4次方
*/
using i4 = __int128;
struct PF
{
	static constexpr ll ERR = -1;
	// 防溢出的取模快速幂
	ll Pow(ll base, ll exp, ll mod)
	{
		ll res = 1;
		base %= mod;
		while (exp)
		{
			if (exp & 1)
				res = (i4)res * base % mod;
			base = (i4)base * base % mod;
			exp >>= 1;
		}
		return res;
	}
	// 是否是质数
	bool MR(ll x)
	{
		if (x < 2)
			return false;
		if (x == 2 or x == 3)
			return true;
		ll d = x - 1;
		ll r = 0;
		while (not(d & 1))
		{
			d >>= 1;
			++r;
		}
		FOR(k, 0, 9)
		{
			ll a = rand() % (x - 2) + 2;
			ll v = Pow(a, d, x);
			if (v == 1 or v == x - 1)
				continue;
			FOR(i, 0, r - 2)
			{
				v = (i4)v * v % x;
				if (v == x - 1)
					break;
			}
			if (v != x - 1)
				return false;
		}
		return true;
	}
	// 一次分解
	ll PR(ll x)
	{
		ll s = 0;
		ll t = 0;
		ll c = (ll)rand() % (x - 1) + 1;
		int step = 0;
		int goal = 1;
		ll val = 1;
		while (true)
		{
			FOR(step, 1, goal)
			{
				t = ((i4)t * t + c) % x;
				val = (i4)val * abs(t - s) % x;
				if (step % 127 == 0)
				{
					ll d = gcd(val, x);
					if (d > 1)
						return d;
				}
			}
			ll d = gcd(val, x);
			if (d > 1)
				return d;
			goal <<= 1;
			s = t;
			val = 1;
		}
		return ERR;
	}
	// 分解质因数
	void DEC(ll x)
	{
		if (x < 2)
			return;
		if (MR(x))
		{
			dt.push_back(x);
			return;
		}
		ll p = x;
		while (p == x)
			p = PR(x);
		DEC(x / p);
		DEC(p);
		return;
	}
	// 质因数种数
	ll sz;
	// 质因数
	VE<ll> dt;
	void Init(void) { srand(time(0)); }
	void Build(ll x)
	{
		dt.clear();
		DEC(x);
		// 去重
		sort(dt.begin(), dt.end());
		dt.erase(unique(dt.begin(), dt.end()), dt.end());
		sz = dt.size();
		return;
	}
};
PF pf;