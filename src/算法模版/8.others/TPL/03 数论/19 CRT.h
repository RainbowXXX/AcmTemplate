// CRT可求解如下形式的一元线性同余方程组（其中r[1]...r[k]两两互质)
// x%a[1]=r[1]...x%a[k]=r[k] 求x
ll CRT(ll k, ll a[], ll r[])
{
	ll n = 1, ans = 0;
	FOR(i, 1, k)
	n = n * r[i];
	FOR(i, 1, k)
	{
		ll m = n / r[i], b, y;
		ExGCD(m, r[i], b, y); // b * m mod r[i] = 1
		ans = (ans + a[i] * m * b % n) % n;
	}
	return (ans % n + n) % n;
}