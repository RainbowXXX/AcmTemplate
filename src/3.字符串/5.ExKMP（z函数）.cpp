namespace ExKMP {
	int z[N];

	void calc(const char* str, int len) {
		int l, r;
		l = r = 0;
		for (int i = 0; i < len; i++) {
			if (i <= r) {
				if (z[i - l] < r - i + 1) z[i] = z[i - l];
				else for (z[i] = r - i + 1; str[z[i]] == str[z[i] + i]; ++z[i]);
			}
			else for (z[i] = 0; str[z[i]] == str[z[i] + i]; ++z[i]);
			if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
		}
	}
}