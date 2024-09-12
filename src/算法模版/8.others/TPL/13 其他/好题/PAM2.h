/*
	字符串S的回文子串集合set中，满足a是b的子串，有多少组a，b可以选
	aaaa 6
	abba 4
	abc 0
*/
template <ll SZ>
struct PAM
{
public:
	ll res;

	void Init(void)
	{
		p = last = sz = 0;
		s[0] = -1;
		fail[0] = 1;
		fail[1] = 0;
		NewNode(0);
		NewNode(-1);
		res = 0;
		return;
	}
	void Push(ll c)
	{
		s[++sz] = c;
		ll cur = GetFail(last);
		if (not nxt[c][cur])
		{
			ll now = NewNode(len[cur] + 2);
			fail[now] = nxt[c][GetFail(fail[cur])];
			nxt[c][cur] = now;
		}
		last = nxt[c][cur];
		return;
	}
	void DFS(ll now, ll cnt)
	{
		ll pos;
		for (pos = now; len[pos] > 0 and not vis[pos]; pos = fail[pos])
		{
			++cnt;
			vis[pos] = 1;
		}
		if (len[now] > 0)
			res += cnt - 1;
		FOR(i, 0, 25)
		if (nxt[i][now])
			DFS(nxt[i][now], cnt);
		for (int i = now; i != pos; i = fail[i])
			vis[i] = false;
		return;
	}

protected:
	ll sz, p, last;
	ll s[SZ];
	ll len[SZ];
	ll fail[SZ];
	ll nxt[26 + 1][SZ];
	bool vis[SZ];

	ll NewNode(ll l)
	{
		FOR(i, 0, 25)
		nxt[i][p] = 0;
		len[p] = l;
		return p++;
	}
	ll GetFail(ll x)
	{
		while (s[sz - len[x] - 1] != s[sz])
			x = fail[x];
		return x;
	}
};
PAM<SZ> pam;
char s[SZ];

void Solve(void)
{
	cin >> (s + 1);
	ll len = strlen(s + 1);
	pam.Init();
	FOR(i, 1, len)
	pam.Push(s[i] - 'a');
	pam.DFS(0, 0);
	pam.DFS(1, 0);
	cout << pam.res << EDL;
	return;
}