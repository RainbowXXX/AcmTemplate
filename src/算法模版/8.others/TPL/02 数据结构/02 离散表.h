/*
离散表
ERR:报错值
sz:当前大小
dt:数据容器 离散化前数据输入进dt
Init:O(1)初始化
Build:O(NlogN)离散化
F(x):O(logN)查询x离散化后的值
AF(x):O(logN)查询x离散化前的值
*/
struct LST
{
	static constexpr ll ERR = -1;
	ll sz;
	VE<ll> dt;
	void Init(void) { dt.clear(); }
	void Build(void)
	{
		std::sort(dt.begin(), dt.end());
		dt.erase(unique(dt.begin(), dt.end()), dt.end());
		sz = dt.size();
		return;
	}
	ll F(ll x)
	{
		ll res = std::lower_bound(dt.begin(), dt.end(), x) - dt.begin() + 1;
		if (res > sz)
			return ERR;
		if (dt[res - 1] != x)
			return ERR;
		return res;
	}
	ll AF(ll x)
	{
		if (not(1 <= x and x <= sz))
			return ERR;
		return dt[x - 1];
	}
};
LST lst;