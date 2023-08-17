// 树状数组
template<typename T = int, size_t Length = N, typename std::enable_if_t<std::is_integral_v<T>, int> = 0>
struct BIT {
private:
	T* tr;
	constexpr T lowbit(T x) { return x & -x; }
public:
	size_t border;
	BIT() : border(N) { tr = new T[Length](); }
	~BIT() { border = 0; delete[] tr; }
	constexpr decltype(auto) add(size_t pos, T val) {
		ensure(pos > 0);
		while (pos <= border) tr[pos] = tr[pos] + val,pos = pos + lowbit(pos);
		return;
	}
	constexpr decltype(auto) quary(size_t pos) {
		T ans = 0;
		while (pos > 0) ans = ans + tr[pos], pos = pos - lowbit(pos);
		return ans;
	}
	constexpr decltype(auto) quary(T l, T r) {
		T ans = quary(r); ans -= quary(l - 1);
		return ans;
	}
};
// 树状数组(区间修改)
template<typename T = int, size_t Length = N, typename std::enable_if_t<std::is_integral_v<T>, int> = 0>
struct SegBIT {
private:
	T* tr1, *tr2;
	constexpr T lowbit(T x) { return x & -x; }
	T quary(T* t, T k) {
		T ret = 0;
		while (k) ret += t[k], k -= lowbit(k);
		return ret;
	}
public:
	size_t border;
	SegBIT() : border(N) { tr1 = new T[Length](); tr2 = new T[Length](); }
	~SegBIT() { border = 0; delete[] tr1; delete[] tr2; }
	constexpr decltype(auto) add(size_t k, T v) {
		ensure(k > 0);
		while (k <= border) tr1[k] += v, tr2[k] += k * v, k += lowbit(k);
	}
	constexpr decltype(auto) add(size_t l, size_t r, T v) {
		add(l, v), add(r + 1, -v);
	}
	T quary(size_t l, size_t r) {
		return (r + 1) * quary(tr1, r) - l * quary(tr1, l - 1) - (quary(tr2, r) - quary(tr2, l - 1));
	}
};