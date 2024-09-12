// 21湖北省赛I
ll n, m;
ll a[SZ][SZ];
ll h[SZ];

void Solve(void)
{
	// 一个n*n矩形
	cin >> n >> m;
	// m个叉
	FOR(i, 1, m)
	{
		// 第i个叉在(x,y)
		ll x, y;
		cin >> x >> y;
		a[x][y] = 1;
	}
	// 统计内部无叉的矩形的个数
	ll ans = 0;
	FOR(i, 1, n)
	{
		FOR(j, 1, n)
		{
			if (a[i][j])
				h[j] = 0;
			else
				++h[j];
		}
		stack<PLL> st;
		ll s = 0;
		FOR(j, 1, n)
		{
			ll len = 1;
			while (not st.empty())
			{
				ll x = st.top().FI;
				ll y = st.top().SE;
				if (x <= h[j])
					break;
				len += st.top().SE;
				s -= st.top().FI * st.top().SE;
				st.pop();
			}
			s += len * h[j];
			st.push({h[j], len});
			ans += s;
		}
	}
	cout << ans << EDL;
	return;
}