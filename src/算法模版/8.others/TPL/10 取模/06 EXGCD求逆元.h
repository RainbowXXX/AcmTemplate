// a * x + b * y == gcd(a, b) == g
ll ExGCD(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll tmp_x, tmp_y;
	ll g = ExGCD(b, a % b, tmp_x, tmp_y);
	x = tmp_y;
	y = tmp_x - a / b * tmp_y;
	return g;
}

// v与mod要求互质 gcd=1
ll Inv(ll v,ll mod)
{
	ll x,y;
	ExGCD(v,mod,x,y);
	return (x%mod+mod)%mod;
}

/***********/

namespace inverse {
	constexpr ll exgcd_mod(const ll& m, const ll& n, ll& x, ll& y, const ll& mod) {
		if (n == 0) {
			x = 1; y = 0;
			return m;
		}
		ll a = 0, b = 1, a1 = 1, b1 = 0, c = m, d = n, q = c / d, r = c % d, t = 0;
		while (r) {
			c = d; d = r;
			t = a1; a1 = a; a = t - q * a % mod;
			t = b1; b1 = b; b = t - q * b % mod;
			q = c / d; r = c % d;
		}
		x = (a % mod + mod) % mod; y = (b % mod + mod) % mod;
		return d;
	}
	constexpr ll inv(const ll& x, const ll& _mod) {
		ll p1 = 0, p2 = 0;
		ll gcd = exgcd_mod(x, _mod, p1, p2, _mod);
		assert(gcd == 1 or gcd == -1);
		return p1;
	}
}