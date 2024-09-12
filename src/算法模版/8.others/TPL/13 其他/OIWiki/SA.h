// s[1,n]
// sa[i]表示将所有后缀排序后第i小的后缀的编号
// rk[i]表示后缀i的排名
// sa[rk[i]]=rk[sa[i]=i
const int N = 1000010;
char s[N];
// key1[i] = rk[id[i]]（作为基数排序的第一关键字数组）
int n, sa[N], rk[N], oldrk[N << 1], id[N], key1[N], cnt[N];
bool cmp(int x, int y, int w) { return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w]; }
int main()
{
	int i, m = 127, p, w;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (i = 1; i <= n; ++i)
		++cnt[rk[i] = s[i]];
	for (i = 1; i <= m; ++i)
		cnt[i] += cnt[i - 1];
	for (i = n; i >= 1; --i)
		sa[cnt[rk[i]]--] = i;
	for (w = 1;; w <<= 1, m = p)
	{ // m=p 就是优化计数排序值域
		for (p = 0, i = n; i > n - w; --i)
			id[++p] = i;
		for (i = 1; i <= n; ++i)
			if (sa[i] > w)
				id[++p] = sa[i] - w;
		memset(cnt, 0, sizeof(cnt));
		for (i = 1; i <= n; ++i)
			++cnt[key1[i] = rk[id[i]]];
		// 注意这里px[i] != i，因为rk没有更新，是上一轮的排名数组
		for (i = 1; i <= m; ++i)
			cnt[i] += cnt[i - 1];
		for (i = n; i >= 1; --i)
			sa[cnt[key1[i]]--] = id[i];
		memcpy(oldrk + 1, rk + 1, n * sizeof(int));
		for (p = 0, i = 1; i <= n; ++i)
			rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
		if (p == n)
		{
			for (int i = 1; i <= n; ++i)
				sa[rk[i]] = i;
			break;
		}
	}
	for (i = 1; i <= n; ++i)
		printf("%d ", sa[i]);
	return 0;
}