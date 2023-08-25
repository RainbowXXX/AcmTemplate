// $$a^t == b (mod p)$$
ll bsgs(ll a, ll b, ll p) {
	a %= p; b %= p;
	if (p == 1 or b == 1) return 0;
	ll d = std::gcd(a, p), res = 0, inv = 1;
	if (d != 1) {
		while (d != 1) {
			// $$ a/d * a^(t-1) == b/d (mod p/d) $$
			if (b % d) return -1;
			res++; b /= d; p /= d; inv = inv * (a / d) % p;
			if (inv == b) return res;
			// $$ a^(t-1) == b (mod p) $$
			d = std::gcd(a, p);
		}
		inv = inverse::inv(inv, p);
		b = b * inv % p;
	}
	// $$ (a^k)^x == b * a^y (mod p) $$
	std::unordered_map<ll, int> mp;
	// 也可以是 k = std::ceil(std::sqrt(phi(p)))
	ll k = std::sqrt(p) + 1, ak = qpow(a, k, p), ay = b;
	for (int i = 0; i < k; i++) mp[ay] = i, ay = ay * a % p; ay = ak;
	for (int i = 1; i <= k; i++) {
		if (mp.count(ay))
			return (res + i * k) - mp[ay];
		ay = ay * ak % p;
	}
	return -1;
}