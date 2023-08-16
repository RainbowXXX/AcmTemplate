// 连续重复子串
int rm[N];
void init() {
	std::fill(rm, rm + N, 0);
	int to = SA::rk[0], t = SA::n;
	for (int i = to - 1; i >= 0; i--)
		rm[i] = t = std::min(SA::ht[i + 1], t);
	t = SA::n; rm[to] = SA::n;
	for (int i = to + 1; i <= SA::n; i++)
		rm[i] = t = std::min(SA::ht[i], t);
}

int getnum() {
	int ans = 0;
	for (int i = 1; i <= SA::n / 2; i++) {
		if (SA::n%i) continue;
		if (rm[SA::rk[i]] == SA::n - i) return SA::n / i;
	}
	return 1;
}