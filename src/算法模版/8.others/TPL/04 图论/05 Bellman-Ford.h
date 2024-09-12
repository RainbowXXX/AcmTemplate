bool ok = true;
while (ok)
{
	ok = false;
	FOR(i, 1, n)
	FOR(j, 1, n)
	if (d[j] + f[j][i] < d[i])
	{
		d[i] = d[j] + f[j][i];
		ok = true;
	}
}