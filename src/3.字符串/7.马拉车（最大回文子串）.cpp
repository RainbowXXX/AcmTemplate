decltype(auto) domanacher(std::string& ms, size_t len, int(&p)[N * 2 + 2]) {
	size_t ans = 0;
	for (int t = 1, r = 0, mid = 0; t < len; ++t) {
		if (t <= r) p[t] = std::min(p[(mid << 1) - t], r - t + 1);
		while (ms[t - p[t]] == ms[t + p[t]]) ++p[t];
		//暴力拓展左右两侧,当t-p[t]==0时，由于data[0]是'~'，自动停止。故不会下标溢出。
		//假若我这里成功暴力扩展了，就意味着到时候r会单调递增，所以manacher是线性的。
		if (p[t] + t > r) r = p[t] + t - 1, mid = t;
		//更新mid和r,保持r是最右的才能保证我们提前确定的部分回文半径尽量多。
		if (p[t] > ans) ans = p[t];
	}
	return ans;
}
decltype(auto) manacher(std::string& s, int(&p)[N * 2 + 2]) {
	size_t len = 1, ans = 0;
	std::string ms(s.size() * 2 + 3, '\0'); ms[0] = '@';
	for (auto ch : s) ms[len++] = '#', ms[len++] = ch; ms[len++] = '#';
	return domanacher(ms, len, p);
}