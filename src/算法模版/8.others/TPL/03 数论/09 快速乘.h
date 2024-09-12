mint QMul(mint lhs, mint rhs)
{
	mint res = 0;
	ll rhsV = rhs.Val();
	while (rhsV)
	{
		if (rhsV & 1)
			res += lhs;
		lhs += lhs;
		rhsV >>= 1;
	}
	return res;
}

// 防溢出
ll QMul(ll lh, ll rh, ll mod) { return (lh * rh - (ll)((db)lh / mod * y) * mod + mod) % mod; }