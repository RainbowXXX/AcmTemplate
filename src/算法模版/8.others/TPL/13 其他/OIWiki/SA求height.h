// height[i]=lcp(sa[i],sa[i-1])
// height[1]=0;
for (i = 1, k = 0; i <= n; ++i)
{
	if (rk[i] == 0)
		continue;
	if (k)
		--k;
	while (s[i + k] == s[sa[rk[i] - 1] + k])
		++k;
	height[rk[i]] = k;
}
// 求lcp 两子串最长公共前缀
// lcp[sa[i],sa[j]]=min({height[i+1...j]});