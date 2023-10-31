//求1-n的所有数字关于mod的逆元
ll inv[N];
void fun(ll n, ll mod) {
	inv[1] = 1;
	for (ll i = 2; i <= n; i++) {
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
}