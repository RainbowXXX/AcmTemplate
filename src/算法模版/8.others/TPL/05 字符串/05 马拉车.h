/*
	sz:当前大小
	s:处理的字符串
	d1[i]:以s[i]为中心点 包括i的最长回文半径长度
	d2[i]:以s[i]为中心偏右点 包括i的最长回文半径长度
	Init(s):O(N)处理
*/
struct MNC
{
	ll sz;
	STR s;
	VE<ll> d1, d2;
	void Init(const STR &s)
	{
		sz = s.size();
		this->s = s;
		d1 = VE<ll>(sz);
		d2 = VE<ll>(sz);
		for (ll i = 0, l = 0, r = -1; i < sz; ++i)
		{
			ll k = (i > r) ? 1 : std::min(d1[l + r - i], r - i + 1);
			while (0 <= i - k && i + k < sz && s[i - k] == s[i + k])
				++k;
			d1[i] = k--;
			if (i + k > r)
			{
				l = i - k;
				r = i + k;
			}
		}
		for (ll i = 0, l = 0, r = -1; i < sz; ++i)
		{
			ll k = (i > r) ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
			while (0 <= i - k - 1 && i + k < sz && s[i - k - 1] == s[i + k])
				++k;
			d2[i] = k--;
			if (i + k > r)
			{
				l = i - k - 1;
				r = i + k;
			}
		}
		return;
	}
};
MNC mnc;