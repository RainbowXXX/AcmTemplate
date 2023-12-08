ll issqrt(ll k) {
	ll t = (ll)(std::sqrt(k) + 0.5);
	if (t * t == k) return t;
	return -1;
}