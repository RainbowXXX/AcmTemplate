mt19937_64 rnd(time(NULL));
ll Rnd(ll l, ll r) { return rnd() % (r - l + 1) + l; }

mt19937 mt(time(0));

srand(time(0));
rand();