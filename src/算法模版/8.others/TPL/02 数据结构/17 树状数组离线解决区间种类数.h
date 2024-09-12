struct Qry{ll l, r;};
//树状数组01
bool CMP(const Qry&lh,const Qry&rh)
{
	if(lh.r!=rh.r) return lh.r<rh.r;
	return lh.l<rh.l;
}
void Run(void)
{
	sort(qry.begin(),qry.end(),CMP);
	std::map<ll,ll> mp;
	bt.Init(n);
	ll now=1;
	for(const auto&[l,r]:qry)
	{
		FOR(j,now,r)
		{
			if(mp.find(a[j])!=mp.end())
				bt.Mdf(mp[a[j]],-1);
			mp[a[j]]=j;
			bt.Mdf(j,1);
		}
		now=r+1;
		//此查询的结果[l,r]的种类数
		ll res=bt.Qry(r)-bt.Qry(l-1);
	}
	return;
}