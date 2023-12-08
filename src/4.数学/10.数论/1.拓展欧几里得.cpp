ll Exgcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) { x = 1; y = 0; return a; }
	ll gcd = Exgcd(b, a % b, x, y);
	ll tmp_x = x; x = y;
	y = tmp_x - a / b * y;
	return gcd;
}

constexpr ll exgcd(const ll& m, const ll& n, ll& x, ll& y) {
	if (n == 0) {
		x = 1; y = 0;
		return m;
	}
	ll a = 0, b = 1, a1 = 1, b1 = 0, c = m, d = n, q = c / d, r = c % d, t = 0;
	while (r) {
		c = d; d = r;
		t = a1; a1 = a; a = t - q * a;
		t = b1; b1 = b; b = t - q * b;
		q = c / d; r = c % d;
	}
	x = a; y = b;
	return d;
}