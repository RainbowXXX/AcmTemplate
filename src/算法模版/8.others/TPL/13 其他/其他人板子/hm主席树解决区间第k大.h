ll a[N];
std::vector<ll> key;
ll getid(ll n) { return std::lower_bound(key.begin(), key.end(), n) - key.begin(); }
class Tree
{
public:
	Tree()
	{
		cnt = 0;
		latest = 0;
		roots[latest] = add();
	}
	Tree(int L, int R)
	{
		cnt = 0;
		latest = 0;
		roots[latest] = add();
		this->L = L;
		this->R = R;
	}
	~Tree() {}
	void init(int L, int R)
	{
		cnt = 0;
		latest = 0;
		roots[latest] = add();
		this->L = L;
		this->R = R;
	}
	// 在ver版本的基础上将x的个数加1,返回最新版本
	size_t AddVer(int ver, int x)
	{
		roots[++latest] = add();
		modify(roots[latest], roots[ver], L, R, x);
		return latest;
	}
	//var版本1到x间的数有多少个
	size_t QueVer(int ver, int x){return query(roots[ver], 1, x, L, R);}
	// 在rver-lver上寻找第k大(k从1计数)
	ll k_thEle(int lver, int rver, int k){return queryk(roots[rver], roots[lver], k, L, R);}

private:
	struct Node
	{
		ll sz;
		size_t lson, rson;
	} tr[N << 2];
	int L, R;
	size_t roots[N], cnt, latest;
	size_t add()
	{
		tr[cnt] = {
			.sz = 0,
			.lson = 0,
			.rson = 0};
		return cnt++;
	}
	void modify(size_t cur, size_t old, int L, int R, int x)
	{
		if (L == R)
		{
			tr[cur].sz = tr[old].sz + 1;
			return;
		}
		int mid = (L + R) / 2;
		// 向左走
		if (x <= mid)
		{
			tr[cur].rson = tr[old].rson;
			tr[cur].sz = tr[old].sz + 1;
			if (tr[cur].lson == 0)
				tr[cur].lson = add();
			modify(tr[cur].lson, tr[old].lson, L, mid, x);
		}
		else
		{
			tr[cur].lson = tr[old].lson;
			tr[cur].sz = tr[old].sz + 1;
			if (tr[cur].rson == 0)
				tr[cur].rson = add();
			modify(tr[cur].rson, tr[old].rson, mid + 1, R, x);
		}
	}
	ll query(size_t cur, int l, int r, int L, int R)
	{
		if (cur == 0)
			return 0;
		if (L >= l and R <= r)
			return tr[cur].sz;
		ll ret = 0;
		int mid = (L + R) / 2;
		if (l <= mid)
			ret += query(tr[cur].lson, l, r, L, mid);
		if (r > mid)
			ret += query(tr[cur].rson, l, r, mid + 1, R);
		return ret;
	}
	ll queryk(size_t cur, size_t old, ll k, int L, int R)
	{
		if (L == R)
			return L;
		int mid = (L + R) / 2;
		ll lsz = tr[tr[cur].lson].sz - tr[tr[old].lson].sz;
		ll rsz = tr[tr[cur].rson].sz - tr[tr[old].rson].sz;
		if (k <= lsz)
			return queryk(tr[cur].lson, tr[old].lson, k, L, mid);
		else
			return queryk(tr[cur].rson, tr[old].rson, k - lsz, mid + 1, R);
	}
} tr;

int main(int argc, char *argv[], char *envp[])
{
	ll n, m;
	std::cin >> n >> m;
	tr.init(0, n);
	key.resize(n);
	for (ll i = 0; i < n; i++)
		std::cin >> a[i], key[i] = a[i];
	std::sort(key.begin(), key.end());
	key.erase(std::unique(key.begin(), key.end()), key.end());
	for (int i = 0; i < n; i++)
	{
		a[i] = getid(a[i]);
		tr.AddVer(i, a[i]);
	}
	for (; m--;)
	{
		int l, r, k, t;
		std::cin >> l >> r >> k;
		t = tr.k_thEle(l - 1, r, k);
		std::cout << key[t] << endl;
	}
	return 0;
}