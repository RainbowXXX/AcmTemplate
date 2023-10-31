//求$\sum^n_{i = 0}{a_1 + q * i}$
ll sum(ll a1, ll q, ll n, int mod) {
	q %= mod; a1 %= mod;
	if (q % mod == 1) {
		return a1 * n % mod;
	}
	ll above = (1 - qpow(q, n, mod)), below = 1 - q;
	above += (above >> 63) & mod; below += (below >> 63) & mod;
	return (a1 * above % mod * inverse::inv(below, mod)) % mod;
}