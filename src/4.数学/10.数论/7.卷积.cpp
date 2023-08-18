namespace cov {
	struct Complex {
	protected:
		double re, im;
	public:
		double real() { return re; }
		double imag() { return im; }
		void real(double value) { re = value; }
		void imag(double value) { im = value; }
		Complex(double re = {}, double im = {}) : re(re), im(im) {}
		Complex(const std::complex<double>& v) { re = v.real(), im = v.imag(); }
		operator std::complex<double>() { return std::complex<double>(re, im); }
		Complex operator+(const Complex& b) const { return Complex(re + b.re, im + b.im); }
		Complex operator-(const Complex& b) const { return Complex(re - b.re, im - b.im); }
		Complex operator*(const Complex& b) const { return Complex(re * b.re - im * b.im, re * b.im + im * b.re); }
	};
	template <int mod1 = 998244353, int mod2 = 1004535809, int mod3 = 469762049>
	struct MttInt {
		int A, B, C;
		static inline ll inv12 = inverse::inv(mod1, mod2), inv12_3 = inverse::inv(1LL * mod1 * mod2 % mod3, mod3), mod12 = 1LL * mod1 * mod2;
		explicit constexpr MttInt() { }
		explicit constexpr MttInt(int __num) : A(__num), B(__num), C(__num) { }
		explicit constexpr MttInt(int __A, int __B, int __C) : A(__A), B(__B), C(__C) { }
		constexpr MttInt& operator = (const int& rhs) { A = B = C = rhs;  return *this; }
		static constexpr MttInt reduce(const MttInt& x) { return MttInt(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3)); }
		constexpr friend MttInt operator - (const MttInt& lhs, const MttInt& rhs) { return reduce(MttInt(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C)); }
		constexpr friend MttInt operator + (const MttInt& lhs, const MttInt& rhs) { return reduce(MttInt(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3)); }
		constexpr friend MttInt operator * (const MttInt& lhs, const MttInt& rhs) { return MttInt(1LL * (lhs.A) * rhs.A % mod1, 1LL * (lhs.B) * rhs.B % mod2, 1LL * (lhs.C) * rhs.C % mod3); }
		constexpr ll val(int ansmod) { ll x = 1LL * (B - A + mod2) % mod2 * inv12 % mod2 * mod1 + A; return (1LL * (C - x % mod3 + mod3) % mod3 * inv12_3 % mod3 * (mod12 % ansmod) % ansmod + x) % ansmod; }
		constexpr MttInt inv() { return MttInt((int)inverse::inv(A, mod1), (int)inverse::inv(B, mod2), (int)inverse::inv(C, mod3)); }
		constexpr MttInt mttnum(int mid) { return MttInt((int)qpow(A, (mod1 - 1) / ((1LL * mid) << 1LL), mod1), (int)qpow(B, (mod2 - 1) / ((1LL * mid) << 1LL), mod2), (int)qpow(C, (mod3 - 1) / ((1LL * mid) << 1LL), mod3)); }
		friend std::istream& operator >> (std::istream& io, MttInt& rhs) { io >> rhs.A; rhs.B = rhs.C = rhs.A; return io; }
	};
	const double pi = acos(-1.0);
	template<class _Ty>
	constexpr void MYCALL change(_Ty* y, int limit) {
		int k;
		for (int i = 1, j = limit / 2; i < limit - 1; i++) {
			if (i < j) std::swap(y[i], y[j]);
			k = limit / 2;
			while (j >= k) {
				j = j - k;
				k = k / 2;
			}
			if (j < k) j += k;
		}
	}
	template<class _Ty, size_t size>
	constexpr void MYCALL print(_Ty(&arry)[size], int length) {
		ensure(length <= size);
		for (int i = length - 1; i >= 0; i--) std::cout << arry[i] << blank;
		std::cout << endl;
	}
	template<size_t size>
	constexpr void MYCALL adjust(ll(&factor)[size], int& len, const int& base) {
		int end, carry = 0;
		for (end = 0; carry || end < len; end++) {
			factor[end] += carry;
			carry = factor[end] / base;
			factor[end] %= base;
		}
		for (; factor[end] == 0 && end > 0; end--);
		len = end + 1;
	}
	template<class ComplexClass, size_t factorsize>
	constexpr void MYCALL FFT(ComplexClass(&factor)[factorsize], int limit, int mode) {
		ComplexClass wn, w, x, y;
		change(factor, limit);
		ensure(limit <= factorsize);
		for (int mid = 1; mid < limit; mid <<= 1) {
			wn = ComplexClass(cos(pi / mid), mode * sin(pi / mid));
			for (int R = mid << 1, i = 0; i < limit; i += R) {
				w = ComplexClass(1, 0);
				for (int k = 0; k < mid; k++, w = w * wn) {
					x = factor[i + k], y = w * factor[i + k + mid];
					factor[i + k] = x + y;
					factor[i + k + mid] = x - y;
				}
			}
		}
		if (mode == 1) return;
		for (int i = 0; i < limit; i++) {
			factor[i].real(factor[i].real() / limit);
			factor[i].imag(factor[i].imag() / limit);
		}
	}
	template<typename IntegralClass, size_t factorsize>
	constexpr void MYCALL NTT(IntegralClass(&factors)[factorsize], int limit, int mode, int g = 3, ll _mod = mod) {
		ll wn, w, inv;
		IntegralClass x, y;
		ensure(limit <= factorsize);
		ensure(((_mod - 1) % limit) == 0);
		ensure(limit == (limit & -limit));
		change(factors, limit);
		for (int mid = 1; mid < limit; mid <<= 1) {
			wn = qpow(g, (_mod - 1) / ((1LL * mid) << 1LL), _mod);
			if (mode == -1) wn = inverse::inv(wn, _mod);
			for (int R = mid << 1, i = 0; i < limit; i += R) {
				w = 1;
				for (int k = 0; k < mid; k++, w = w * wn % _mod) {
					x = factors[i + k], y = factors[i + k + mid] * w % _mod;
					factors[i + k] = (x + y) % _mod;
					factors[i + k + mid] = (x - y + _mod) % _mod;
				}
			}
		}
		if (mode != -1) return;
		inv = inverse::inv(limit, _mod);
		for (int i = 0; i < limit; i++) {
			factors[i] = factors[i] * inv % _mod;
		}
	}
	template<size_t factorsize, int mod1, int mod2, int mod3>
	constexpr void MYCALL MTT(MttInt<mod1, mod2, mod3>(&factors)[factorsize], int limit, int mode, MttInt<mod1, mod2, mod3> g = MttInt<mod1, mod2, mod3>(3)) {
		MttInt<mod1, mod2, mod3> x, y, wn, w, inv;
		ensure(limit <= factorsize);
		ensure(((mod1 - 1) % limit) == 0);
		ensure(((mod2 - 1) % limit) == 0);
		ensure(((mod3 - 1) % limit) == 0);
		ensure(limit == (limit & -limit));
		change(factors, limit);
		for (int mid = 1; mid < limit; mid <<= 1) {
			wn = g.mttnum(mid);
			if (mode == -1) wn = wn.inv();
			for (int R = mid << 1, i = 0; i < limit; i += R) {
				w.A = w.B = w.C = 1;
				for (int k = 0; k < mid; k++, w = w * wn) {
					x = factors[i + k], y = factors[i + k + mid] * w;
					factors[i + k] = x + y;
					factors[i + k + mid] = x - y;
				}
			}
		}
		if (mode != -1) return;
		inv.A = inv.B = inv.C = limit; inv = inv.inv();
		for (int i = 0; i < limit; i++) {
			factors[i] = factors[i] * inv;
		}
	}
	template<size_t size1, size_t size2, size_t anssize>
	inline int MYCALL fftmul(ll(&factor1)[size1], int len1, ll(&factor2)[size2], int len2, ll(&ans)[anssize]) {
		int limit = 1, t = len1 + len2;
		static std::Complex y[std::max(size1, size2)];
		while (limit < t) limit <<= 1;
		ensure(limit <= size1); ensure(limit <= size2); ensure(limit <= anssize);
		for (int i = 0; i < limit; i++) {
			y[i].real(i < len1 ? (double)factor1[i] : 0);
			y[i].imag(i < len2 ? (double)factor2[i] : 0);
		}
		FFT(y, limit, 1);
		for (int i = 0; i < limit; i++) y[i] = y[i] * y[i];
		FFT(y, limit, -1);
		for (int i = 0; i < limit; i++) ans[i] = (ll)(y[i].imag() / 2.0 + 0.5);
		return limit;
	}
	template<typename IntegralClass, size_t size1, size_t size2, size_t anssize>
	constexpr int MYCALL nttmul(IntegralClass(&factor1)[size1], int len1, IntegralClass(&factor2)[size2], int len2, IntegralClass(&ans)[anssize], int g = 3, ll _mod = mod) {
		int limit = 1, t = len1 + len2;
		while (limit < t) limit <<= 1;
		ensure(limit <= size1); ensure(limit <= size2); ensure(limit <= anssize);
		for (int i = len1; i < limit; i++) factor1[i] = 0;
		if (&factor1 != &factor2)
			for (int i = len2; i < limit; i++) factor2[i] = 0;
		NTT(factor1, limit, 1, g, _mod); if (&factor1 != &factor2) NTT(factor2, limit, 1, g, _mod);
		if (&factor1 != &factor2)
			for (int i = 0; i < limit; i++) ans[i] = factor1[i] * factor2[i] % _mod;
		else
			for (int i = 0; i < limit; i++) ans[i] = factor1[i] * factor1[i] % _mod;
		NTT(ans, limit, -1, g, _mod);
		return limit;
	}
	template<size_t size1, size_t size2, size_t anssize, int mod1, int mod2, int mod3>
	constexpr int MYCALL mttmul(MttInt<mod1, mod2, mod3>(&factor1)[size1], int len1, MttInt<mod1, mod2, mod3>(&factor2)[size2], int len2, ll(&ans)[anssize], int endmod = mod, MttInt<mod1, mod2, mod3> g = MttInt<mod1, mod2, mod3>(3)) {
		int limit;
		for (limit = 1; limit < len1 + len2; limit <<= 1);
		ensure(limit <= size1); ensure(limit <= size2); ensure(limit <= anssize);
		for (int i = len1; i < limit; i++) factor1[i] = 0;
		if (&factor1 != &factor2)
			for (int i = len2; i < limit; i++) factor2[i] = 0;
		MTT(factor1, limit, 1, g); MTT(factor2, limit, 1, g);
		for (int i = 0; i < limit; i++) factor1[i] = factor1[i] * factor2[i];
		MTT(factor1, limit, -1, g);
		for (int i = 0; i < limit; i++) ans[i] = factor1[i].val(endmod);
		return limit;
	}
	template<size_t size1, size_t size2, size_t anssize>
	constexpr void MYCALL add(ll(&factor1)[size1], int len1, ll(&factor2)[size2], int len2, ll(&ans)[anssize], int& anslen) {
		ll len, i, carry = 0, tem;
		len = std::max(len1, len2);
		for (i = 0; i < len; i++) {
			tem = carry + factor1[i] + factor2[i];
			ans[i] = tem % 10; carry = tem / 10;
		}
		for (i = len; carry; i++)
			ans[i] = carry % 10, carry /= 10;
		anslen = i - 1;
	}
	template<size_t size1, size_t size2, size_t anssize>
	constexpr void MYCALL mul(ll(&factor1)[size1], int len1, ll(&factor2)[size2], int len2, ll(&ans)[anssize], int& anslen, bool flag = false, int g = 3, ll _mod = mod) {
		int len, carry = 0;
		len = cov::nttmul(factor1, len1, factor2, len2, ans, g, _mod);
		adjust(ans, anslen, 10);
		if (flag) {
			if (ans != factor1) cov::NTT(factor1, len, -1, _mod);
			if (ans != factor2 && factor2 != factor1) cov::NTT(factor2, len, -1, _mod);
		}
	}
	template<typename IntegralClass, size_t size1, size_t size2>
	inline MYCALL void PolyInv(int deg, IntegralClass(&factor1)[size1], IntegralClass(&ansfactor)[size2]) {
		int orz = 1, limit, t, key, deep;
		static IntegralClass tem[size1];
		ansfactor[0] = inverse::inv(factor1[0]);
		for (limit = 1, deep = 0; limit <= deg; limit <<= 1) deep++;
		std::fill(tem, tem + limit, 0);
		t = limit - deg; deg = 1;
		for (key = 0, limit >>= 1; limit; limit >>= 1) key = (key << 1) | (t & 1), t >>= 1;
		for (int i = 0; i < deep; i++) {
			deg <<= 1; deg -= key & 0x1; key >>= 1;
			while (orz < (deg << 1)) orz <<= 1;
			std::copy(factor1, factor1 + deg, tem);
			cov::NTT(tem, orz, 1); cov::NTT(ansfactor, orz, 1);
			for (int i = 0; i < orz; ++i) ansfactor[i] = (2 - tem[i] * ansfactor[i] % mod + mod) % mod * ansfactor[i] % mod;
			cov::NTT(ansfactor, orz, -1); std::fill(ansfactor + deg, ansfactor + orz, 0);
		}
	}
	namespace fwt {
		ll x, y;
		template<size_t factorsize>
		constexpr void fwt_or(ll(&factors)[factorsize], int limit, int mode, int _mod = mod) {
			ensure(limit <= factorsize);
			ensure(limit == (limit & -limit));
			for (int i = 2, j = 1; i <= limit; j = i, i <<= 1)
				for (int t = 0; t < limit; t += i)
					for (int k = t; k < j + t; ++k)
						factors[k + j] = (factors[k + j] + factors[k] * mode) % _mod;
		}
		template<size_t factorsize>
		constexpr void fwt_and(ll(&factors)[factorsize], int limit, int mode, int _mod = mod) {
			ensure(limit <= factorsize);
			ensure(limit == (limit & -limit));
			for (int i = 2, j = 1; i <= limit; j = i, i <<= 1)
				for (int t = 0; t < limit; t += i)
					for (int k = t; k < j + t; ++k)
						factors[k] = (factors[k] + factors[k + j] * mode) % _mod;
		}
		template<size_t factorsize>
		constexpr void fwt_xor(ll(&factors)[factorsize], int limit, int mode, int _mod = mod) {
			ensure(limit <= factorsize);
			ensure(limit == (limit & -limit));
			if (mode == -1) mode = inverse::inv(2, _mod);
			for (int i = 2, j = 1; i <= limit; j = i, i <<= 1)
				for (int t = 0; t < limit; t += i)
					for (int k = t; k < j + t; ++k) {
						y = factors[k] - factors[k + j]; y += (y >> 63) & _mod;
						x = factors[k] + factors[k + j] - _mod; x += (x >> 63) & _mod;
						factors[k] = x * mode % _mod; factors[k + j] = (y * mode % _mod + _mod) % _mod;
					}
		}
	}
}