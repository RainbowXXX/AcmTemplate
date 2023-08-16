std::unordered_map<int, ll> mp;

//a^x==b(mod n)
int BSGS(int a, int b, int mod) { // n是不是素数都可以
	if (b == 1) return 0;
	int m = sqrt(mod * 1.0);
	long long  x = 1, p = 1;
	for (int i = 0; i < m; ++i, p = p * a % mod) mp[p * b % mod] = i;

	for (ll i = m;; i += m) {
		x = x * p % mod;
		if (mp.count(x)) {
			return i - mp[x];
		}
		if (i > mod) break;
	}
	return -1;
}