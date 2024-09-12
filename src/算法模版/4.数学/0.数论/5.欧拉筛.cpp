bool not_prime[N];
int primes[N], tot;

void Sieve(int n) {
	tot = 0;
	not_prime[0] = not_prime[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (not not_prime[i]) primes[tot++] = i;
		for (int j = 0; j < tot and i * primes[j] <= n; j++) {
			not_prime[i * primes[j]] = true;
			if (i % primes[j] == 0) break;
		}
	}
}