class PresidentTree
{
public:
	PresidentTree() {
		cnt = 0;
		latest = 0;
		//roots.resize(N);
		//tr.resize(N << 2);
		roots[latest] = add();
	}
	PresidentTree(int L, int R) {
		cnt = 0;
		latest = 0;
		this->L = L;
		this->R = R;
		//roots.resize(N);
		//tr.resize(N << 2);
		roots[latest] = add();
	}

	~PresidentTree() { }

	void init(int L, int R) {
		cnt = 0;
		latest = 0;
		roots[latest] = add();
		this->L = L;
		this->R = R;
	}

	void clear() {
		cnt = 0;
		latest = 0;
		roots[latest] = add();
	}

	//在ver版本的基础上将x加k,返回最新版本
	size_t AddVer(int ver, int x, int k) {
		roots[++latest] = add();
		modify(roots[latest], roots[ver], L, R, x, k);
		return latest;
	}

	size_t QueVer(int verl, int verr, int l, int r) {
		return query(roots[verl], roots[verr], l, r, L, R);
	}

	//在rver-lver上寻找第k大(k从1计数)
	ll k_thEle(int lver, int rver, int k) {
		return queryk(roots[rver], roots[lver], k, L, R);
	}

protected:
	struct Node {
		ll nums;
		size_t lson, rson;
	};
	size_t add() {
		tr[cnt] = {
			.nums = 0,
			.lson = 0,
			.rson = 0
		};
		return cnt++;
	}
	// 无论是old节点 还是cur节点的范围都是 L到R
	// 参照old节点 修改cur节点 总体效果是将x的个数加k
	void modify(size_t cur, size_t old, int L, int R, int x, int k) {
		if (L == R) { tr[cur].nums = tr[old].nums + k; return; }
		int mid = (L + R) / 2;
		if (x <= mid) {
			tr[cur].rson = tr[old].rson;
			tr[cur].nums = tr[old].nums + k;
			if (tr[cur].lson == 0) tr[cur].lson = add();
			modify(tr[cur].lson, tr[old].lson, L, mid, x, k);
		}
		else {
			tr[cur].lson = tr[old].lson;
			tr[cur].nums = tr[old].nums + k;
			if (tr[cur].rson == 0) tr[cur].rson = add();
			modify(tr[cur].rson, tr[old].rson, mid + 1, R, x, k);
		}
	}
	// 查询r版本减去l版本 上的l到r的数字个数
	ll query(size_t verl, size_t verr, int l, int r, int L, int R) {
		if (L >= l and R <= r) return tr[verr].nums - tr[verl].nums;
		ll ret = 0;
		int mid = (L + R) / 2;
		if (l <= mid) ret += query(tr[verl].lson, tr[verr].lson, l, r, L, mid);
		if (r > mid) ret += query(tr[verl].rson, tr[verr].rson, l, r, mid + 1, R);
		return ret;
	}
	// 查询某个版本 上的l到r的数字个数
	ll query(size_t cur, int l, int r, int L, int R) {
		if (cur == 0) return 0;
		if (L >= l and R <= r) return tr[cur].nums;
		ll ret = 0;
		int mid = (L + R) / 2;
		if (l <= mid) ret += query(tr[cur].lson, l, r, L, mid);
		if (r > mid) ret += query(tr[cur].rson, l, r, mid + 1, R);
		return ret;
	}
	// 查询版本r减去版本l 上的第k大的数字
	ll queryk(size_t verl, size_t verr, ll k, int L, int R) {
		if (L == R) return L;
		int mid = (L + R) / 2;
		ll lsz = tr[tr[verr].lson].nums - tr[tr[verl].lson].nums;
		ll rsz = tr[tr[verr].rson].nums - tr[tr[verl].rson].nums;
		if (k <= lsz) return queryk(tr[verl].lson, tr[verr].lson, k, L, mid);
		else return queryk(tr[verl].rson, tr[verr].rson, k - lsz, mid + 1, R);
	}
private:
	int L, R;
	size_t cnt, latest;
	//std::vector<Node> tr;
	//std::vector<size_t> roots;
	Node tr[N << 2];
	size_t roots[N];
};

//**********************************************************************************************
//*                    以下为vector重构版本 (非必要情况下一定要用这个!!!!!!!!)                    *
//**********************************************************************************************

class PresidentTree
{
public:
	PresidentTree() {
		this->L = -1;
		this->R = -1;

		tr.clear();
		roots.clear();
		tr.reserve(N << 2);
		roots.emplace_back(add());
	}
	PresidentTree(ll L, ll R) {
		this->L = L;
		this->R = R;

		tr.clear();
		roots.clear();
		tr.reserve(N << 2);
		roots.emplace_back(add());
	}

	~PresidentTree() { }

	void init(ll L, ll R) {
		this->L = L;
		this->R = R;

		tr.clear();
		roots.clear();
		roots.emplace_back(add());
	}

	void clear() {
		tr.clear();
		roots.clear();
		roots.emplace_back(add());
	}

	size_t lastest() const {
		return roots.size() - 1;
	}

	//在ver版本的基础上将x加k,返回最新版本
	size_t AddVer(int ver, int x, int k) {
		roots.emplace_back(add());
		modify(roots.back(), roots[ver], L, R, x, k);
		return roots.size() - 1;
	}

	// 查询在rver-lver上有多少值在[l,r]的范围内(闭区间)
	size_t QueVer(int verl, int verr, int l, int r) const {
		return query(roots[verl], roots[verr], l, r, L, R);
	}

	//在verr-verl上寻找第k大(k从1计数)
	ll k_thEle(int verl, int verr, int k) const {
		return queryk(roots[verl], roots[verr], k, L, R);
	}

protected:
	struct Node {
		int nums;
		int lson, rson;
	};
	size_t add() {
		tr.emplace_back(Node{
			.nums = 0,
			.lson = 0,
			.rson = 0
			});
		return tr.size() - 1;
	}
	// 无论是old节点 还是cur节点的范围都是 L到R
	// 参照old节点 修改cur节点 总体效果是将x的个数加k
	void modify(size_t cur, size_t old, int L, int R, int x, int k) {
		if (L == R) { tr[cur].nums = tr[old].nums + k; return; }
		int mid = (L + R) / 2;
		if (x <= mid) {
			tr[cur].rson = tr[old].rson;
			tr[cur].nums = tr[old].nums + k;
			if (tr[cur].lson == 0) tr[cur].lson = add();
			modify(tr[cur].lson, tr[old].lson, L, mid, x, k);
		}
		else {
			tr[cur].lson = tr[old].lson;
			tr[cur].nums = tr[old].nums + k;
			if (tr[cur].rson == 0) tr[cur].rson = add();
			modify(tr[cur].rson, tr[old].rson, mid + 1, R, x, k);
		}
	}
	// 查询r版本减去l版本 上的l到r的数字个数
	ll query(size_t verl, size_t verr, int l, int r, int L, int R) const {
		if (L >= l and R <= r) return tr[verr].nums - tr[verl].nums;
		ll ret = 0;
		int mid = (L + R) / 2;
		if (l <= mid) ret += query(tr[verl].lson, tr[verr].lson, l, r, L, mid);
		if (r > mid) ret += query(tr[verl].rson, tr[verr].rson, l, r, mid + 1, R);
		return ret;
	}
	// 查询某个版本 上的l到r的数字个数
	ll query(size_t cur, int l, int r, int L, int R) const {
		if (cur == 0) return 0;
		if (L >= l and R <= r) return tr[cur].nums;
		ll ret = 0;
		int mid = (L + R) / 2;
		if (l <= mid) ret += query(tr[cur].lson, l, r, L, mid);
		if (r > mid) ret += query(tr[cur].rson, l, r, mid + 1, R);
		return ret;
	}
	// 查询版本r减去版本l 上的第k大的数字
	ll queryk(size_t verl, size_t verr, ll k, int L, int R) const {
		if (L == R) return L;
		int mid = (L + R) / 2;
		ll lsz = tr[tr[verr].lson].nums - tr[tr[verl].lson].nums;
		ll rsz = tr[tr[verr].rson].nums - tr[tr[verl].rson].nums;
		if (k <= lsz) return queryk(tr[verl].lson, tr[verr].lson, k, L, mid);
		else return queryk(tr[verl].rson, tr[verr].rson, k - lsz, mid + 1, R);
	}
private:
	ll L, R;
	std::vector<Node> tr;
	std::vector<size_t> roots;
};
