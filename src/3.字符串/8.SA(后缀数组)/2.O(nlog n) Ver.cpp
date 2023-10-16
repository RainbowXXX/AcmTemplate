//兼容SA_IS
namespace SA {
	int cnt[N], tp[N], rk[N], ht[N], sa[N], n, m;

	inline bool cmp(int x, int y, int w) {
		return tp[x] == tp[y] && tp[x + w] == tp[y + w];
	}

	// m代表值域是[0,m)
	void calc_sa(const char* s, int _n, int _m) {
		// n = _n, m = _m;
		n = _n + 1, m = _m;
		std::fill(cnt, cnt + m, 0);
		// 计算单个字符的时候的sa数组和rk数组
		for (int i = 0; i < n; i++) sa[i] = i, cnt[rk[i] = s[i]]++;
		for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[i]]] = i;

		int p = -1;
		for (int k = 1; k <= n; k <<= 1, m = p + 1, p = -1) {
			for (int i = n - 1; i >= n - k; i--) tp[++p] = i;
			for (int i = 0; i < n; i++) if (sa[i] >= k) tp[++p] = sa[i] - k;

			// tp现在按照第二关键字排好了
			std::fill(cnt, cnt + m, 0);
			for (int i = 0; i <= p; ++i) ++cnt[rk[tp[i]]];
			for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
			for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[tp[i]]]] = tp[i];

			p = 0; std::copy(rk, rk + n, tp); rk[sa[0]] = 0;
			for (int i = 1; i < n; i++) rk[sa[i]] = cmp(sa[i - 1], sa[i], k) ? p : ++p;
			if ((p + 1) == n) break;
		}

		for (int i = 0; i < n; i++) rk[sa[i]] = i;
	}

	void get_height(const char* s) {
		int j = 0;
		for (int i = 0, k = 0; i < n; i++) {
			if (rk[i] == 0) continue;
			if (k) k--;
			j = sa[rk[i] - 1];
			while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
			ht[rk[i]] = k;
		}
	}
}