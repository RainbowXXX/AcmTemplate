constexpr ll CrtTwo(ll a1, ll m1, ll a2, ll m2, ll mod, ll inv12, ll inv21) {
	return (qmul(inv21, m2 * a1, mod) + qmul(inv12, m1 * a2, mod)) % mod;
}