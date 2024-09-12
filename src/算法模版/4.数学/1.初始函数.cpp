//(x^n)%mod
constexpr ll qmul(ll p1, ll p2, ll mod) {
	ensure(mod < 500000000000000000LL);
	p1 %= mod; p2 %= mod;
	ll ret = (p1 * p2 - (ll)((point_t)p1 * p2 / mod) * mod) % mod;
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
constexpr ull qmul_safe(ull x, ull n, ull mod) {
	if (mod < 500000000000000000LL)
		return qmul(x, n, mod);
#ifdef __SIZEOF_INT128__
	if (mod < 1000000000000000000LL) {
		x %= mod; n %= mod;
		return (__int128)x * n % mod;
	}
#endif // __SIZEOF_INT128__
	return mul(x, n, mod);
}
constexpr ull qpow(ull x, ull n, int mod) {
	x %= mod;
	ull ret = 1, tem = x;
	while (n) {
		if (n & 0x1) ret = ret * tem % mod;
		tem = tem * tem % mod; n >>= 1;
	}
	return ret;
}
constexpr ull qpow_safe(ull x, ull n, ull mod) {
	ull ret = 1, tem = x % mod;
	if (mod < 50000000000000000LL) {
		while (n) {
			if (n & 0x1) ret = qmul(ret, tem, mod);
			tem = qmul(tem, tem, mod);
			n >>= 1;
		}
	}
#ifdef __SIZEOF_INT128__
	else if (mod < 1000000000000000000LL) {
		while (n) {
			if (n & 0x1) ret = (__int128)ret * tem % mod;
			tem = (__int128)tem * tem % mod;
			n >>= 1;
		}
	}
#endif // __SIZEOF_INT128__
	else {
		while (n) {
			if (n & 0x1) ret = mul(ret, tem, mod);
			tem = mul(tem, tem, mod);
			n >>= 1;
		}
	}
	return ret;
}

template <typename T, typename std::enable_if<std::is_unsigned_v<T>, int>::type = 0>
constexpr T getSgn(T val) { return 0; }
template <typename T, typename std::enable_if<std::is_signed_v<T>, int>::type = 0>
constexpr T getSgn(T val) { return val >> (((sizeof(T)) << 2) - 1); }