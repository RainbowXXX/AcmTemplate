ll Exgcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) { x = 1; y = 0; return a; }
	ll gcd = Exgcd(b, a % b, x, y);
	ll tmp_x = x; x = y;
	y = tmp_x - a / b * y;
	return gcd;
}