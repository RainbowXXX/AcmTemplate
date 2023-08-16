int prime[N], tot;
bool not_prime[N];

void Sieve(int n) {
	tot = 0;
	not_prime[0] = not_prime[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (not not_prime[i]) prime[tot++] = i;
		for (int j = 0; j < tot and i * prime[j] <= n; j++) {
			not_prime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}