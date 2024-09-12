// O(N)计算x的欧拉函数值
ll EulerPHI(ll x)
{
	ll res = x;
	for (ll i = 2; i * i <= x; i++)
		if (x % i == 0)
		{
			res = res / i * (i - 1);
			while (x % i == 0)
				x /= i;
		}
	if (x > 1)
		res = res / x * (x - 1);
	return res;
}