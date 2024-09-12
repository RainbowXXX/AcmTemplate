struct BigIntSimple {
	static const int BIGINT_BASE = 10000;
	static const int BIGINT_DIGITS = 4;

	int sign; // 1表示正数，-1表示负数
	std::vector<int> v;

	//定义0也需要长度1
	BigIntSimple() {
		sign = 1;
		v.push_back(0);
	}
	template <typename T, typename std::enable_if<std::is_integral_v<T>, int>::type = 0>
	BigIntSimple(T n) {
		*this = n;
	}
	//判断是否为0
	bool iszero() const {
		return v.size() == 1 && v.back() == 0;
	}
	//消除前导0并修正符号
	void trim() {
		while (v.back() == 0 && v.size() > 1)
			v.pop_back();
		if (iszero()) sign = 1;
	}
	//获取pos位置上的数值，用于防越界，简化输入处理
	int get(size_t pos) const {
		if (pos >= v.size()) return 0;
		return v[pos];
	}
	//绝对值大小比较
	bool absless(const BigIntSimple& b) const {
		if (v.size() != b.v.size()) return v.size() < b.v.size();
		for (size_t i = v.size() - 1; i < v.size(); --i)
			if (v[i] != b.v[i]) return v[i] < b.v[i];
		return false;
	}
	//字符串输入
	void set(const char* s) {
		v.clear();
		sign = 1;
		//处理负号
		while (*s == '-')
			sign = -sign, ++s;
		//先按数位直接存入数组里
		for (size_t i = 0; s[i]; ++i)
			v.push_back(s[i] - '0');
		std::reverse(v.begin(), v.end());
		//压位处理，e是压位后的长度
		size_t e = (v.size() + BIGINT_DIGITS - 1) / BIGINT_DIGITS;
		for (size_t i = 0, j = 0; i < e; ++i, j += BIGINT_DIGITS) {
			v[i] = v[j]; //设置压位的最低位
			//高位的按每一位上的数值乘以m，m是该位的权值
			for (size_t k = 1, m = 10; k < BIGINT_DIGITS; ++k, m *= 10)
				v[i] += (int)(get(j + k) * m);
		}
		//修正压位后的长度
		if (e) {
			v.resize(e);
			trim();
		}
		else {
			v.resize(1);
		}
	}
	//字符串输出
	std::string to_str() const {
		std::string s;
		for (size_t i = 0; i < v.size(); ++i) {
			int d = v[i];
			//拆开压位
			for (size_t k = 0; k < BIGINT_DIGITS; ++k) {
				s += d % 10 + '0';
				d /= 10;
			}
		}
		//去除前导0
		while (s.size() > 1 && s.back() == '0')
			s.pop_back();
		//补符号
		if (sign < 0) s += '-';
		//不要忘记要逆序
		std::reverse(s.begin(), s.end());
		return s;
	}
	//字符串输入
	void set(std::string s, int base, const std::vector<int>& inmap) {
		sign = 1;
		v.push_back(0);
		for (auto ch : s) {
			(*this) = (*this) * base;
			(*this) = (*this) + inmap[ch];
		}
	}
	//字符串输出
	std::string to_str(int base, const std::vector<int>& outmap) const {
		std::string ret;
		BigIntSimple t = (*this);
		if (t.iszero()) return "0";
		while (not t.iszero()) {
			ret += outmap[(t % base).get(0)];
			t = t / base;
		}
		std::reverse(ret.begin(), ret.end());
		return ret;
	}

	bool operator<(const BigIntSimple& b) const {
		if (sign == b.sign) {
			return sign > 0 ? absless(b) : b.absless(*this);
		}
		else {
			return sign < 0;
		}
	}
	template <typename T, typename std::enable_if<std::is_signed_v<T>, int>::type = 0>
	BigIntSimple& operator=(T n) {
		v.clear();
		sign = n >= 0 ? 1 : -1;
		for (n = abs(n); n; n /= BIGINT_BASE)
			v.push_back(n % BIGINT_BASE);
		if (v.empty()) v.push_back(0);
		return *this;
	}
	template <typename T, typename std::enable_if<std::is_unsigned_v<T>, int>::type = 0>
	BigIntSimple& operator=(T n) {
		v.clear();
		sign = 1;
		for (; n; n /= BIGINT_BASE)
			v.push_back(n % BIGINT_BASE);
		if (v.empty()) v.push_back(0);
		return *this;
	}

	BigIntSimple& operator=(const std::string& s) {
		set(s.c_str());
		return *this;
	}

	BigIntSimple operator-() const {
		BigIntSimple r = *this;
		r.sign = -r.sign;
		return r;
	}

	BigIntSimple operator+(const BigIntSimple& b) const {
		//符号不同时转换为减法
		if (sign != b.sign) return *this - -b;
		BigIntSimple r = *this;
		//填充高位
		if (r.v.size() < b.v.size()) r.v.resize(b.v.size());
		int carry = 0;
		//逐位相加
		for (size_t i = 0; i < b.v.size(); ++i) {
			carry += r.v[i] + b.v[i] - BIGINT_BASE;
			r.v[i] = carry - BIGINT_BASE * (carry >> 31);
			carry = (carry >> 31) + 1;
		}
		//处理进位，拆两个循环来写是避免做 i < b.v.size() 的判断
		for (size_t i = b.v.size(); carry && i < r.v.size(); ++i) {
			carry += r.v[i] - BIGINT_BASE;
			r.v[i] = carry - BIGINT_BASE * (carry >> 31);
			carry = (carry >> 31) + 1;
		}
		//处理升位进位
		if (carry) r.v.push_back(carry);
		return r;
	}

	BigIntSimple& subtract(const BigIntSimple& b) {
		int borrow = 0;
		//先处理b的长度
		for (size_t i = 0; i < b.v.size(); ++i) {
			borrow += v[i] - b.v[i];
			v[i] = borrow;
			v[i] -= BIGINT_BASE * (borrow >>= 31);
		}
		//如果还有借位就继续处理
		for (size_t i = b.v.size(); borrow; ++i) {
			borrow += v[i];
			v[i] = borrow;
			v[i] -= BIGINT_BASE * (borrow >>= 31);
		}
		//减法可能会出现前导0需要消去
		trim();
		return *this;
	}

	BigIntSimple operator-(const BigIntSimple& b) const {
		//符号不同时转换为加法
		if (sign != b.sign) return (*this) + -b;
		if (absless(b)) { //保证大数减小数
			BigIntSimple r = b;
			return -r.subtract(*this);
		}
		else {
			BigIntSimple r = *this;
			return r.subtract(b);
		}
	}

	BigIntSimple operator*(const BigIntSimple& b) const {
		// r记录相加结果
		BigIntSimple r;
		r.v.resize(v.size() + b.v.size()); //初始化长度
		for (size_t j = 0; j < v.size(); ++j) {
			int carry = 0, m = v[j]; // m用来缓存乘数
			// carry可能很大，只能使用求模的办法，此循环与加法部分几乎相同，就多乘了个m
			for (size_t i = 0; i < b.v.size(); ++i) {
				carry += r.v[i + j] + b.v[i] * m;
				r.v[i + j] = carry % BIGINT_BASE;
				carry /= BIGINT_BASE;
			}
			r.v[j + b.v.size()] += carry;
		}
		r.trim();
		r.sign = sign * b.sign;
		return r;
	}

	//对b乘以mul再左移offset的结果相减，为除法服务
	BigIntSimple& sub_mul(const BigIntSimple& b, int mul, size_t offset) {
		if (mul == 0) return *this;
		int borrow = 0;
		//与减法不同的是，borrow可能很大，不能使用减法的写法
		for (size_t i = 0; i < b.v.size(); ++i) {
			borrow += v[i + offset] - b.v[i] * mul - BIGINT_BASE + 1;
			v[i + offset] = borrow % BIGINT_BASE + BIGINT_BASE - 1;
			borrow /= BIGINT_BASE;
		}
		//如果还有借位就继续处理
		for (size_t i = b.v.size(); borrow; ++i) {
			borrow += v[i + offset] - BIGINT_BASE + 1;
			v[i + offset] = borrow % BIGINT_BASE + BIGINT_BASE - 1;
			borrow /= BIGINT_BASE;
		}
		return *this;
	}

	BigIntSimple div_mod(const BigIntSimple& b, BigIntSimple& r) const {
		BigIntSimple d;
		r = *this;
		if (absless(b)) return d;
		d.v.resize(v.size() - b.v.size() + 1);
		//提前算好除数的最高三位+1的倒数，若最高三位是a3,a2,a1
		//那么db是a3+a2/base+(a1+1)/base^2的倒数，最后用乘法估商的每一位
		//此法在BIGINT_BASE<=32768时可在int32范围内用
		//但即使使用int64，那么也只有BIGINT_BASE<=131072时可用（受double的精度限制）
		//能保证估计结果q'与实际结果q的关系满足q'<=q<=q'+1
		//所以每一位的试商平均只需要一次，只要后面再统一处理进位即可
		//如果要使用更大的base，那么需要更换其它试商方案
		double t = (b.get((unsigned)b.v.size() - 2) +
			(b.get((unsigned)b.v.size() - 3) + 1.0) / BIGINT_BASE);
		double db = 1.0 / (b.v.back() + t / BIGINT_BASE);
		for (size_t i = v.size() - 1, j = d.v.size() - 1; j <= v.size();) {
			int rm = r.get(i + 1) * BIGINT_BASE + r.get(i);
			int m = std::max((int)(db * rm), r.get(i + 1));
			r.sub_mul(b, m, j);
			d.v[j] += m;
			if (!r.get(i + 1)) //检查最高位是否已为0，避免极端情况
				--i, --j;
		}
		r.trim();
		//修正结果的个位
		int carry = 0;
		while (!r.absless(b)) {
			r.subtract(b);
			++carry;
		}
		//修正每一位的进位
		for (size_t i = 0; i < d.v.size(); ++i) {
			carry += d.v[i];
			d.v[i] = carry % BIGINT_BASE;
			carry /= BIGINT_BASE;
		}
		d.trim();
		d.sign = sign * b.sign;
		return d;
	}

	BigIntSimple operator/(const BigIntSimple& b) const {
		BigIntSimple r;
		return div_mod(b, r);
	}

	BigIntSimple operator%(const BigIntSimple& b) const {
		return *this - *this / b * b;
	}

	friend std::istream& operator>>(std::istream& io, BigIntSimple& num) {
		std::string s;
		io >> s; num.set(s.c_str());
		return io;
	}
	friend std::ostream& operator<<(std::ostream& io, const BigIntSimple& num) {
		io << num.to_str();
		return io;
	}
};
bool operator == (BigIntSimple a, BigIntSimple b) {
	if (a.v.size() != b.v.size())return false;
	const size_t sz = a.v.size();
	for (int i = 0; i < sz; i++) {
		if (a.v[i] != b.v[i])return false;
	}
	return true;
}
bool operator <=(BigIntSimple a, BigIntSimple b) {
	return (a < b) || (a == b);
}
BigIntSimple Zero;
BigIntSimple gcd(BigIntSimple a, BigIntSimple b) {
	if (b.iszero())return a;
	return gcd(b, a % b);
}
using bigint = BigIntSimple;