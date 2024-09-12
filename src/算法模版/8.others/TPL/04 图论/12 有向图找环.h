// ABC311
ll n;
ll a[SZ];
VE<ll> cycle;

ll cycleBegin, cycleEnd;
bool vis[SZ];
bool inStk[SZ];
ll pre[SZ];

void DFS(ll x)
{
	vis[x] = true;
	inStk[x] = true;

	ll nxt = a[x];
	if (vis[nxt])
	{
		if (inStk[nxt])
		{
			cycleBegin = nxt;
			cycleEnd = x;
		}
	}
	else
	{
		pre[nxt] = x;
		DFS(nxt);
	}

	inStk[x] = false;
}

void FindCycle(void)
{
	FOR(i, 1, n)
	if (not vis[i])
		DFS(i);

	cycle.push_back(cycleBegin);
	ll x = cycleEnd;
	while (x != cycleBegin)
	{
		cycle.push_back(x);
		x = pre[x];
	}
}
void Solve(void)
{
	cin >> n;
	FOR(i, 1, n)
	cin >> a[i];

	FindCycle();
	ll m = cycle.size();
	cout << m << EDL;
	ROF(i, m - 1, 0)
	cout << cycle[i] << (i == 0 ? EDL : WS);
	return;
}