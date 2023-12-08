template <long long P>
struct ModInt
{
public:
	ModInt() : _v(0) {}
	template <typename _Ty>
	ModInt(_Ty v) { _v = ((long long)v % P + P) % P; }
	long long val() const { return _v; }
	ModInt& operator++()
	{
		++_v;
		if (_v == P)
			_v = 0;
		return *this;
	}
	ModInt& operator--()
	{
		if (_v == 0)
			_v = P;
		--_v;
		return *this;
	}
	ModInt operator++(int)
	{
		ModInt oldVal = *this;
		++* this;
		return oldVal;
	}
	ModInt operator--(int)
	{
		ModInt oldVal = *this;
		--* this;
		return oldVal;
	}
	ModInt& operator+=(const ModInt& rhs)
	{
		_v += rhs._v;
		_v %= P;
		return *this;
	}
	ModInt& operator-=(const ModInt& rhs)
	{
		_v -= rhs._v;
		_v = (_v + P) % P;
		return *this;
	}
	ModInt& operator*=(const ModInt& rhs)
	{
		_v *= rhs._v;
		_v %= P;
		return *this;
	}
	ModInt& operator/=(const ModInt& rhs) { return *this *= rhs.inv(); }
	ModInt operator+() const { return *this; }
	ModInt operator-() const { return ModInt() - *this; }
	ModInt pow(long long exp) const
	{
		// assert(exp>=0);
		ModInt res = 1;
		ModInt base = *this;
		while (exp)
		{
			if (exp & 1)
				res *= base;
			base *= base;
			exp >>= 1;
		}
		return res;
	}
	ModInt inv() const
	{
		// assert(_v);
		return pow(P - 2);
	}
	friend ModInt operator+(const ModInt& lhs, const ModInt& rhs)
	{
		ModInt res = lhs;
		res += rhs;
		return res;
	}
	friend ModInt operator-(const ModInt& lhs, const ModInt& rhs)
	{
		ModInt res = lhs;
		res -= rhs;
		return res;
	}
	friend ModInt operator*(const ModInt& lhs, const ModInt& rhs)
	{
		ModInt res = lhs;
		res *= rhs;
		return res;
	}
	friend ModInt operator/(const ModInt& lhs, const ModInt& rhs)
	{
		ModInt res = lhs;
		res /= rhs;
		return res;
	}
	friend bool operator==(const ModInt& lhs, const ModInt& rhs) { return lhs._v == rhs._v; }
	friend bool operator!=(const ModInt& lhs, const ModInt& rhs) { return lhs._v != rhs._v; }
	friend std::istream& operator>>(std::istream& is, ModInt& aim)
	{
		long long tmp;
		is >> tmp;
		aim = ModInt(tmp);
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const ModInt& aim) { return os << aim.val(); }

private:
	long long _v;
};
using mint = ModInt<MOD>;