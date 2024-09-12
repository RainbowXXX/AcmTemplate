// phi[mod]是mod的欧拉函数值
ll Inv(ll x,ll mod)
{
	if(x%mod!=0)
		return Pow(x,phi[mod]-1,mod);
	return -1;
}