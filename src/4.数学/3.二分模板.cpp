//当 l = mid + 1时, mid = l + r >>1;
//当 l = mid 时， mid = l + r + 1 >>1;
int l = 1, r = n;
while (r > l) {
	int mid = l + r >> 1;
	if (sum(tr,mid)>=a[i]+1) r = mid;
	else l = mid+1;
}