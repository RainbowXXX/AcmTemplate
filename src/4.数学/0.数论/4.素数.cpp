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

	constexpr ll rho(ll x, ll c, ll n) {
		ll ret = qmul_safe(x, x, n) + c - n;
		return ret + ((ret >> 63) & n);
	}
	constexpr ll rho2(ll x, ll c, ll n) {
		return rho(rho(x, c, n), c, n);
	}

	constexpr ll pollardRho(ll n, ll c) {
		ll start = 0, cur = 0, f = 0;
		cur = rho(cur, c, n), f = rho2(f, c, n);
		for (int chunk = 1; cur != f; chunk <<= 1) {
			ll val = 1, fac = 0, t = 0;
			for (int stp = 1; stp <= chunk; stp++) {
				cur = rho(cur, c, n), f = rho2(f, c, n);
				t = (cur - start) >> 63;
				val = qmul_safe(val, (cur - start + t) ^ t, n);
				if ((stp & 0x7f) == 0) {
					fac = std::gcd(val, n);
					if (fac > 1) return fac;
				}
			}
			fac = std::gcd(val, n);
			if (fac > 1) return fac;
			start = cur;
		}
		return n;
	}

	inline ll maxFac(ll n) {
		ll k = 0, p = 0, ret = 0;
		std::queue<ll> qu; qu.emplace(n);
		while (not qu.empty()) {
			k = qu.front(), p = k; qu.pop();
			if (k <= ret or k < 2) continue;
			if (millerRabin(k)) {
				ret = ret > k ? ret : k;
				continue;
			}
			while (p >= k) p = pollardRho(k, rand() % (k - 1) + 1);
			while ((k % p) == 0) k /= p;
			qu.emplace(k), qu.emplace(p);
		}
		return ret;
	}

	inline std::vector<ll> primeFac(ll n) {
		ll k = 0, p = 0;
		std::vector<ll> ret;
		std::queue<ll> qu; qu.emplace(n);
		while (not qu.empty()) {
			k = qu.front(), p = k; qu.pop();
			if (k < 2) continue;
			if (millerRabin(k)) {
				ret.emplace_back(k);
				continue;
			}
			while (p >= k) p = pollardRho(k, rand() % (k - 1) + 1);
			while ((k % p) == 0) k /= p;
			qu.emplace(k), qu.emplace(p);
		}
		std::sort(ret.begin(), ret.end());
		ret.erase(std::unique(ret.begin(), ret.end()), ret.end());
		return ret;
	}

	constexpr ll calcPhi(ll n) {
		ll result = n;
		for (ll i = 2; i * i <= n; i++) {
			if (n % i == 0) {
				while (n % i == 0) n /= i;
				result -= result / i;
			}
		}
		if (n > 1) result -= result / n;
		return result;
	}
	template <ll n> constexpr ll getPhi = calcPhi(n);

	constexpr ull eqpow(ull x, ull n, int mod, int phi = -1) {
		if (phi == -1)
			phi = static_cast<int>(calcPhi(mod));
		if (std::gcd(x, mod) == 1)
			n = n % phi;
		else if (n >= phi)
			n = n % phi + phi;
		return qpow(x, n, mod);
	}

	ll eqpows(int mod) { return 1; }
	template <class T, class ...Args>
	ll eqpows(int mod, T base, Args... args) {
		static ll ret, tem, f;
		ll phi = calcPhi(mod), next;
		next = eqpows(phi, args...);
		if (std::gcd(base, mod) == 1)
			next = next % phi;
		else if (next >= phi)
			next = next % phi + phi;
		ret = 1; tem = base; f = 0;
		while (next) {
			if (next & 0x1) {
				ret = ret * tem;
				if (ret >= mod) f = 1, ret %= mod;
			}
			tem = qmul_safe(tem, tem, mod); next >>= 1;
		}
		if (f) ret += mod;
		return ret;
	}
	template <class T, class ...Args>
	ll qpow_big(int mod, T base, Args... args) {
		return eqpows(mod, base, args...) % mod;
	}
}