/*
并查集
sz:当前大小
Init(sz):O(N)初始化
Find(m):O(1)查询m的s
Same(lh,rh):O(1)判断lh和rh的s是否相同
Merge(s,m):O(1)把m并入s
Size(m):O(1)查询m的s的大小
*/
template <ll SZ>
struct DSU
{
public:
	ll sz;
	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 0, sz)
		{
			fa[i] = i;
			siz[i] = 1;
		}
		return;
	}
	// ll Find(ll m) { return fa[m] == m ? m : fa[m] = Find(fa[m]); }
	ll Find(ll m)
	{
		while (m != fa[m])
			m = fa[m] = fa[fa[m]];
		return m;
	}
	bool Same(ll lh, ll rh) { return Find(lh) == Find(rh); }
	bool Merge(ll s, ll m)
	{
		s = Find(s);
		m = Find(m);
		if (s == m)
			return false;
		siz[s] += siz[m];
		fa[m] = s;
		return true;
	}
	ll Size(ll m) { return siz[Find(m)]; }

protected:
	ll fa[SZ + 1];
	ll siz[SZ + 1];
};
DSU<SZ> dsu;