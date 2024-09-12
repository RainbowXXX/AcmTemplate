ll tem[N];
ll merge_sort(ll* l, ll* r)
{
	if (l + 1 == r) return 0;
	ll ret = 0;
	ll tot = 0;
	ll* mid = l + ((r - l) >> 1);

	ret += merge_sort(l, mid);
	ret += merge_sort(mid, r);

	ll* i = l, * j = mid;
	while (i != mid && j != r)
	{
		if (*i <= *j) tem[tot++] = *(i++), ret += j - mid;
		else tem[tot++] = *(j++);
	}
	while (i != mid) tem[tot++] = *(i++), ret += j - mid;
	while (j != r) tem[tot++] = *(j++);
	for (i = l, j = tem; i != r; i++, j++) *i = *j;

	return ret;
}