/*
欧拉筛
判素数 批处理欧拉函数值 质因子分解
NUL:空值
sz:当前筛的范围
f[i]:判断i是否是素数
phi[i]:i的欧拉函数值
vis[i]:能整除i的最小数
prm:[1,sz]中的素数
Init(sz):O(N)筛前sz个数
Build(x):O(logN)对x分解质因数
*/
template <ll SZ>
struct ES
{
	static constexpr ll NUL = -114514;
	ll sz;
	bool f[SZ + 1];
	ll phi[SZ + 1];
	ll vis[SZ + 1];
	VE<ll> prm;
	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 0, sz)
		{
			f[i] = true;
			phi[i] = vis[i] = NUL;
		}
		prm.clear();
		f[0] = f[1] = false;
		phi[1] = 1;
		FOR(i, 2, sz)
		{
			if (f[i])
			{
				prm.push_back(i);
				phi[i] = i - 1;
				vis[i] = i;
			}
			for (const auto &p : prm)
			{
				if (i * p > sz)
					break;
				f[i * p] = false;
				vis[i * p] = p;
				if (i % p != 0)
					phi[i * p] = phi[i] * phi[p];
				else
				{
					phi[i * p] = phi[i] * p;
					break;
				}
			}
		}
		return;
	}
	std::map<ll, ll> Build(ll x)
	{
		std::map<ll, ll> res;
		while (vis[x] != NUL)
		{
			++res[vis[x]];
			x /= vis[x];
		}
		return res;
	}
};
ES<SZ> es;