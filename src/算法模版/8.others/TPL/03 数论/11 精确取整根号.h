ll Sqrt(ll x)
{
	ll res = sqrt(x);
	while (res * res < x)
		++res;
	while (res * res > x)
		--res;
	return res;
}