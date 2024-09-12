// 用一组比较小的质数表示一个大的整数
// 满足a<∏(i=1,k)p[i](p[i]为质数，或者两两互质)
// FOR(i,1,k) a==a[i]%p[i]
// Then a==x[1]+x[2]p[1]+x[3]p[1]p[2]+...x[k]p[1]...p[k-1]
// 求x[]
// 令r[i][j] 为 p[i] 在模 p[j] 意义下的 逆
FOR(i, 0, k - 1)
{
	x[i] = a[i];
	FOR(j, 0, i - 1)
	{
		x[i] = r[j][i] * (x[i] - x[j]);
		x[i] = x[i] % p[i];
		if (x[i] < 0)
			x[i] += p[i];
	}
}