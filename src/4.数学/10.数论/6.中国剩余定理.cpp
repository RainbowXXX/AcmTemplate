constexpr ll CrtTwo(ll a1, ll m1, ll a2, ll m2, ll mod, ll inv12, ll inv21) {
	return (qmul(inv21, m2 * a1, mod) + qmul(inv12, m1 * a2, mod)) % mod;
}
ll crt(const ll f[], const ll m[],const ll n, ll mod = -1) {
	ll ans = 0;
	if (mod == -1) {
		mod = 1;
		for (int i = 0; i < n; i++) mod *= m[i];
	}
	for (int i = 0; i < n; i++) {
		ll t = f[i] % m[i];
		ans += qmul_safe(qmul_safe(t, (mod / m[i]), mod), inverse::inv(mod / m[i], m[i]), mod);
	}
	return ans % mod;
}
