/*
多重背包
共kind_sz种物品 最多花费cost_sz
第i种物品花费cost[i] 贡献val[i] 最多拿cnt[i]次
花费i最多得到f[i]的贡献
kind_sz:共kind_sz种物品
cost_sz:最多花费cost_sz
cost[i]:第i件的花费
val[i]:第i件的贡献
cnt[i]:第i件的上限数量
f[i]:花费i最多得到的贡献
Init(kind_sz,cost_sz):O(cost_sz)初始化
Build():O(kind_sz * cost_sz * cnt_sz)跑DP得到f[]
*/
template <ll KIND_SZ, ll COST_SZ>
struct Pack
{
	ll kind_sz, cost_sz;
	ll cost[KIND_SZ + 1], val[KIND_SZ + 1], cnt[KIND_SZ + 1];
	ll f[COST_SZ + 1];
	void Init(ll kind_sz, ll cost_sz)
	{
		this->kind_sz = kind_sz;
		this->cost_sz = cost_sz;
		FOR(i, 0, cost_sz)
		f[i] = 0;
		return;
	}
	void Build(void)
	{
		FOR(i, 1, kind_sz)
		{
			if (cost_sz <= cost[i] * cnt[i])
			{
				FOR(j, cost[i], cost_sz)
				f[j] = max(f[j], f[j - cost[i]] + val[i]);
			}
			else
			{
				ll pos = 1;
				ll tot = cnt[i];
				while (pos <= tot)
				{
					ROF(j, cost_sz, cost[i] * pos)
					f[j] = max(f[j], f[j - cost[i] * pos] + val[i] * pos);
					tot -= pos;
					pos <<= 1;
				}
				ROF(j, cost_sz, cost[i] * tot)
				f[j] = max(f[j], f[j - cost[i] * tot] + val[i] * tot);
			}
		}
		return;
	}
};
Pack<SZ, SZ> pack;
/*
可以把每个物品拆成log份物品进行零一背包（二进制）
多重背包
n个物品 V大小背包 最多得f[V]价值
i号物品占体积v[i] 价值w[i] 最多p[i]个
每个物品最多拿p[i]个 可以不拿
FOR(i,1,n)
{
	ll num=min(p[i],V/v[i]);
	for(ll k=1LL;num>0;k<<=1)
	{
		if(k>num) k=num;
		num-=k;
		ROF(j,V,v[i]*k)
		Max(f[j],f[j-v[i]*k]+w[i]*k);
	}
}
*/