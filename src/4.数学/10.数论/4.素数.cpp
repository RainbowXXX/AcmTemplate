namespace prime {
	//拓展到2^63
	constexpr bool millerRabin(ll n) {
		if (n <= 1) return false;
		if (n == 2 || n == 7 || n == 61) return true;
		if (n % 2 == 0) return false;
		ll d = n - 1;
		while ((d & 0x1) == 0) d >>= 1;
		constexpr ll magic[9] = { 2,7,61,325, 9375, 28178, 450775, 9780504, 1795265022 };

		for (int i = n < 1000000000 ? 2 : 8; i >= 0; i--) {
			ll a = magic[i] % n; if (a == 0) continue;
			ll t = d, y = qpow_safe(a, t, n);
			while (t != n - 1 and y != 1 and y != n - 1)
				y = mul(y, y, n), t <<= 1;
			if (y != n - 1 && t % 2 == 0) return false;
		}
		return true;
	}
	constexpr bool primeTest(ll n) {
		if (n < 2) return false;
		if (n == 2 or n == 3) return true;
		if (n % 6 != 1 and n % 6 != 5) return false;
		for (ll i = 5; i * i <= n; i += 6)
			if (n % i == 0 or n % (i + 2) == 0)
				return false;
		return true;
	}
	template <ll n> constexpr bool is_prime = primeTest(n);
	// 求原根,m必须是素数
	constexpr int primitive_root_constexpr(int m) {
		if (m == 2) return 1;
		if (m == 167772161) return 3;
		if (m == 469762049) return 3;
		if (m == 754974721) return 11;
		if (m == 998244353) return 3;
		int cnt = 1, x = (m - 1) / 2, divs[20] = {}; divs[0] = 2;
		while (x % 2 == 0) x /= 2;
		for (int i = 3; static_cast<ll>(i) * i <= x; i += 2) {
			if (x % i == 0) {
				divs[cnt++] = i;
				while (x % i == 0) x /= i;
			}
		}
		if (x > 1) divs[cnt++] = x;
		for (int g = 2;; g++) {
			bool ok = true;
			for (int i = 0; i < cnt; i++) {
				if (qpow(g, (m - 1) / divs[i], m) == 1) {
					ok = false; break;
				}
			}
			if (ok) return g;
		}
	}
	template <ll m, typename std::enable_if<primeTest(m), int>::type = 0> constexpr int primitive_root = primitive_root_constexpr(m);
}