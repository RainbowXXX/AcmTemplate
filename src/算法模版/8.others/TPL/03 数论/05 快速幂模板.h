// O(logN)计算base ^ exp
template <typename T>
T Pow(T base, ll exp)
{
	assert(exp >= 0);
	T res = 1;
	while (exp)
	{
		if (exp & 1)
			res *= base;
		base *= base;
		exp >>= 1;
	}
	return res;
}