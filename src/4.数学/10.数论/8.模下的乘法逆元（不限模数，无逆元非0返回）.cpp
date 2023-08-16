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
	constexpr ll inv(const ll& x, const ll& _mod = mod) {
		ll p1 = 0, p2 = 0;
		ll gcd = exgcd_mod(x, _mod, p1, p2, _mod);
		ensure(gcd == 1 || gcd == -1);
		return p1;
	}
}