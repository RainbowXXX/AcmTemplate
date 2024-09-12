const int maxn = 5010;
const int maxm = 400010;
const int inf = 2e9;
int n, m, s, t, k, u, v, ww, H[maxn], cnt[maxn];
int cur, h[maxn], nxt[maxm], p[maxm], w[maxm];
int cur1, h1[maxn], nxt1[maxm], p1[maxm], w1[maxm];
bool tf[maxn];
void add_edge(int x, int y, double z)
{
	cur++;
	nxt[cur] = h[x];
	h[x] = cur;
	p[cur] = y;
	w[cur] = z;
}
void add_edge1(int x, int y, double z)
{
	cur1++;
	nxt1[cur1] = h1[x];
	h1[x] = cur1;
	p1[cur1] = y;
	w1[cur1] = z;
}
struct node
{
	int x, v;
	bool operator<(node a) const { return v + H[x] > a.v + H[a.x]; }
};
priority_queue<node> q;
struct node2
{
	int x, v;
	bool operator<(node2 a) const { return v > a.v; }
} x;
priority_queue<node2> Q;
int main()
{
	scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
	while (m--)
	{
		scanf("%d%d%d", &u, &v, &ww);
		add_edge(u, v, ww);
		add_edge1(v, u, ww);
	}
	for (int i = 1; i <= n; i++)
		H[i] = inf;
	Q.push({t, 0});
	while (!Q.empty())
	{
		x = Q.top();
		Q.pop();
		if (tf[x.x])
			continue;
		tf[x.x] = true;
		H[x.x] = x.v;
		for (int j = h1[x.x]; j; j = nxt1[j])
			Q.push({p1[j], x.v + w1[j]});
	}
	q.push({s, 0});
	while (!q.empty())
	{
		node x = q.top();
		q.pop();
		cnt[x.x]++;
		if (x.x == t && cnt[x.x] == k)
		{
			printf("%d\n", x.v);
			return 0;
		}
		if (cnt[x.x] > k)
			continue;
		for (int j = h[x.x]; j; j = nxt[j])
			q.push({p[j], x.v + w[j]});
	}
	printf("-1\n");
	return 0;
}