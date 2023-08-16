using ChType = char;
const size_t Sigma = 65;
const size_t Length = N;
struct ACM {
private:
	struct ACMEdge {
		int next[Sigma];
		int cnt, end, fail;
	} tr[Length];
	int tot, root;
public:
	constexpr int getkey(const ChType& ch) const {
		return ch - 'a';
	}
	int add() {
		std::fill(tr[tot].next, tr[tot].next + Sigma, -1);
		tr[tot].cnt = 0; tr[tot].end = -1; tr[tot].fail = -1;
		return tot++;
	}
	void clear() {
		tot = 0;
		root = add();
	}
	void insert(const ChType* str, size_t len, int id) {
		int p = root, key;
		for (size_t i = 0; i < len; i++) {
			key = getkey(str[i]);
			if (tr[p].next[key] == -1)
				p = tr[p].next[key] = add();
			else
				p = tr[p].next[key];
		}
		tr[p].cnt++; tr[p].end = id;
	}

	void build() {
		std::queue<int> qu;
		for (int i = 0; i < Sigma; i++) {
			if (tr[root].next[i] != -1) {
				tr[tr[root].next[i]].fail = root;
				qu.emplace(tr[root].next[i]);
			} else tr[root].next[i] = root;
		}

		while (!qu.empty()) {
			int p = qu.front(); qu.pop();
			for (int i = 0; i < Sigma; i++) {
				int& q = tr[p].next[i];
				if (q != -1) {
					tr[q].fail = tr[tr[p].fail].next[i];
					qu.emplace(q);
				} else q = tr[tr[p].fail].next[i];
			}
		}
	}

	// 求模式串出现了几个
	int quary(const ChType* str, size_t len) {
		int now = 0, ans = 0;
		for (int i = 0; i < len; ++i) {
			now = tr[now].next[getkey(str[i])];
			for (int t = now; t && tr[t].cnt != -1; t = tr[t].fail) {
				ans += tr[t].cnt;
				tr[t].cnt = -1;
			}
		}
		return ans;
	}
	// 求模式串出现次数
	int val[N];
	void querytimes(const ChType* str, size_t len) {
		int u = root;
		for (int i = 0; i < len; i++) {
			int v = getkey(str[i]);
			int k = tr[u].next[v];
			while (k > root) {
				if (tr[k].end != -1)
					val[tr[k].end]++;
				k = tr[k].fail;
			}
			u = tr[u].next[v];
		}
	}
};