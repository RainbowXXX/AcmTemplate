ll Ai(ll a0, ll d, ll i) { return a0 + i * d; }
/*
a1[i]=a10+d1*i
a2[i]=a20+d2*i
f[i]=a1[i]*a2[i]
Sn=Sum(f[1]~f[n])
*/
ll Sn(ll a10, ll d1, ll a20, ll d2, ll n)
{
	ll res = 0;
	res += a10 * a20 * n;
	res += d1 * d2 * (n * (n + 1) * (n * 2 + 1) / 6);
	res += a20 * d1 * (n * (n + 1) / 2);
	res += a10 * d2 * (n * (n + 1) / 2);
	return res;
}