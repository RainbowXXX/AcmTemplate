ll GCD(ll lhs, ll rhs)
{
	if (lhs == 0)
		return rhs;
	if (rhs == 0)
		return lhs;
	return GCD(rhs, lhs % rhs);
}
ll GCD(ll lhs, ll rhs)
{
	if (lhs < rhs)
		swap(lhs, rhs);
	while (rhs != 0)
	{
		ll r = lhs % rhs;
		lhs = rhs;
		rhs = r;
	}
	return lhs;
}

ll LCM(ll lhs, ll rhs) { return lhs / gcd(lhs, rhs) * rhs; }