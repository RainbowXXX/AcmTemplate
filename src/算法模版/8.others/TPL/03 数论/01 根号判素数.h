// O(sqrtN)判x是否素数
bool IsPrm(ll x)
{
	if (x < 2)
		return false;
	if (x == 2 or x == 3)
		return true;
	if (x % 6 != 1 and x % 6 != 5)
		return false;
	for (ll i = 5; i * i <= x; i += 6)
		if (x % i == 0 or x % (i + 2) == 0)
			return false;
	return true;
}