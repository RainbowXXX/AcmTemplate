//(x^n)%mod
constexpr ll qmul(ll p1, ll p2, ll mod) {
	ensure(mod < 500000000000000000LL);
	ll ret = (p1 * p2 - (ll)((long double)p1 * p2 / mod) * mod) % mod;
	return (ret + ((ret >> 63) & mod));
}
constexpr ll mul(ll x, ll n, ll mod) {
	x %= mod; n %= mod;
	ll ret = 0, tmp = x;
	while (n) {
		if (n & 1) {
			ret += tmp - mod;
			ret += (ret >> 63) & mod;
		}
		tmp <<= 1; n >>= 1;
		if (tmp > mod) tmp -= mod;
	}
	return ret;
}
constexpr ull mul(ull x, ull n, ull mod) {
	x %= mod; n %= mod;
	ull ret = 0, tmp = x;
	while (n) {
		if (n & 1) {
			ret += tmp - mod;
			ret += static_cast<ull>(((static_cast<ll>(ret)) >> 63) & mod);
		}
		tmp <<= 1; n >>= 1;
		if (tmp > mod) tmp -= mod;
	}
	return ret;
}