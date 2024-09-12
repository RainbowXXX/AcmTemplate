ll Ai(ll a0, ll d, ll i){return a0 + i * d};
ll Sn(ll a0, ll d, ll n)
{
	ll a1 = Ai(a0, d, 1);
	ll an = Ai(a0, d, n);
	return (a1 + an) * n / 2;
}