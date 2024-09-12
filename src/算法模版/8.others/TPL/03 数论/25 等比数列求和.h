ll Ai(ll a0, ll q, ll i) { return a0 * Pow(q, i); }
ll Sn(ll a0, ll q, ll n) { return (q == 1 ? n * a0 : a0 * q * (Pow(q, n) - 1) / (q - 1)); }