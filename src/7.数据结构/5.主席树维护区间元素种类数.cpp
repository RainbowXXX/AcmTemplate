// 统计区间种类中元素种类数, 要先离散化, 离散化后的值从1开始(0不能使用)
// 构造的时候会初始化Max和R,否则需要在build和quary之前先init
class InterKindTree {
public:
	InterKindTree() : tr(), Max(0) { }
	// 数组中的数字的范围是 [1,Max] (闭区间), 下标范围是[1,R] (闭区间)
	InterKindTree(ll R, ll Max) : tr(0, R), Max(Max) { }

	~InterKindTree() { }

	// 数组中的数字的范围是 [1,Max] (闭区间), 下标范围是[1,R] (闭区间)
	void init(ll R, ll Max) {
		this->Max = Max;
		tr.init(0, R);
		head.clear();
		next.clear();
	}

	void clear() {
		tr.clear();
		head.clear();
		next.clear();
	}

	// 下标以1开始,使用前一定要构造或者init!!!!!!,多组要清空!!!
	template<typename Ty>
	void build(std::vector<Ty>& arr) {
		build(arr.data(), arr.size());
	}

	// 下标以1开始,使用前一定要构造或者init!!!!!!,多组要清空!!!
	template<typename Ty>
	void build(Ty* arr, size_t len) {
		tr.clear();
		head.clear();
		next.clear();

		// 如果当前的数字没有前驱, 默认让其在下标0出现一次(值不允许是0的原因)
		next.resize(len, 0);
		head.resize(Max + 1);

		len--;
		arr += len;

		// 求每个数字的前驱(上一个与当前数字相同的数字的下标)
		for (size_t i = len; i >= 1; i--, arr--) {
			auto& item = head[*arr];
			// 如果之前出现过这个数字
			if (item) next[item] = i;
			// 当前数字最后一次出现在i
			item = i;
		}

		int cur = 0;
		for (size_t i = 1; i <= len; i++) {
			tr.AddVer(cur++, next[i], 1);
		}
	}

	ll query(ll l, ll r) {
		if (r < l) return 0;
		return tr.QueVer(l - 1, r, 0, l - 1);
	}

protected:
	ll Max;
	PresidentTree tr;
	std::vector<size_t> head, next;
};