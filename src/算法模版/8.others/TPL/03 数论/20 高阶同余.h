// a,p互质, 求x使得 ax ≡ b (mode p) 无解返回-1;
// a^(k%(p-1))≡a^k (mod p)  设x=i*m-j<=p, m=ceil(sqrt(p) ),i和j只需枚举1到m 复杂度为o(m);
// 得到a^(i*m-j)≡b (mod p)，移项的(a^m)^i≡b*a^j (mod p);

ll qpow(ll a, ll b, ll p)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
ll baby_step(ll a, ll b, ll p)
{
	std::map<int, int> hash;
	hash.clear();
	b %= p;
	int m = ceil(sqrt(p)); // 对sqrt(p)向上取整

	// 对j枚举 ，将(b*a^j , j)存入表中
	for (int j = 0; j < m; j++)
	{
		ll val = b * qpow(a, j, p) % p;
		hash[val] = j;
	}
	// 对i枚举，查询(a^m)*i是否在表中，存在 x为i*m-j;
	if (a == 0)
		if (b == 0)
			return 1;
		else
			return -1;

	a = qpow(a, m, p);
	for (int i = 0; i <= m; i++)
	{
		ll val = qpow(a, i, p);
		if (hash.find(val) == hash.end())
			continue;
		int j = hash[val];
		if (i * m - j >= 0)
			return i * m - j;
	}
	return -1;
}