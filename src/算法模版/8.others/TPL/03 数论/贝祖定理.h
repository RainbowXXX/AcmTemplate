ll xmin, ymin;
ll xmax, ymax;
/*
	@param ax+by=c
	@return {x0,z} x0:[0,z-1] ax0+by=c;

	If c%gcd(a,b)!=0 it returns {-1,-1}
	all the solutions satisfy x=x0+kz;
	y can be obtained by ax+by=c

	@note x_min, y_min, x_max, y_max (all >= 0)
	is also in the function
*/
PLL exgcd(ll a, ll b, ll c)
{
	std::function<ll(ll, ll, ll &, ll &)> ex_gcd = [&](ll a, ll b, ll &x, ll &y) -> ll
	{
		if (b == 0)
		{
			x = 1;
			y = 0;
			return a;
		}
		ll x1, y1;
		ll g = ex_gcd(b, a % b, x1, y1);
		x = y1;
		y = x1 - a / b * y1;
		return g;
	};
	ll x, y;
	ll g = ex_gcd(a, b, x, y);
	if (c % g != 0)
		return {-1, -1};
	ll z = std::abs(b / g);
	x = (__int128_t)x * (c / g) % z;
	x = (x + z) % z;
	ll w = std::abs(a / g);
	y = (__int128_t)y * (c / g) % w;
	y = (y + w) % w;
	xmin = x, ymin = y;
	xmax = (c - (__int128_t)b * ymin) / a;
	ymax = (c - (__int128_t)a * xmin) / b;
	return {x, z};
}