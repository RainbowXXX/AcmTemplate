template <ll MOD>
struct ModInt
{
public:
	ModInt() : v(0) {}
	template <typename T>
	ModInt(T x)
	{
		ll tmp = x;
		if (0 <= tmp and tmp < MOD)
			v = tmp;
		else if (MOD <= tmp)
			v = tmp % MOD;
		else
			v = (tmp % MOD + MOD) % MOD;
	}
	ll Val(void) const { return v; }
	ModInt Pow(ll exp) const
	{
		assert(exp >= 0);
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
	ModInt Inv(void) const
	{
		assert(v != 0);
		return Pow(MOD - 2);
	}
	ModInt &operator++()
	{
		++v;
		if (v == MOD)
			v = 0;
		return *this;
	}
	ModInt &operator--()
	{
		if (v == 0)
			v = MOD;
		--v;
		return *this;
	}
	ModInt operator++(int)
	{
		ModInt oldVal = *this;
		++*this;
		return oldVal;
	}
	ModInt operator--(int)
	{
		ModInt oldVal = *this;
		--*this;
		return oldVal;
	}
	ModInt &operator+=(const ModInt &rh)
	{
		v += rh.v;
		if (MOD <= v)
			v -= MOD;
		return *this;
	}
	ModInt &operator-=(const ModInt &rh)
	{
		v -= rh.v;
		if (v < 0)
			v += MOD;
		return *this;
	}
	ModInt &operator*=(const ModInt &rh)
	{
		v *= rh.v;
		v %= MOD;
		return *this;
	}
	ModInt &operator/=(const ModInt &rh) { return *this *= rh.Inv(); }
	ModInt operator+() const { return *this; }
	ModInt operator-() const { return ModInt(0) - *this; }
	friend ModInt operator+(const ModInt &lh, const ModInt &rh)
	{
		ModInt res = lh;
		res += rh;
		return res;
	}
	friend ModInt operator-(const ModInt &lh, const ModInt &rh)
	{
		ModInt res = lh;
		res -= rh;
		return res;
	}
	friend ModInt operator*(const ModInt &lh, const ModInt &rh)
	{
		ModInt res = lh;
		res *= rh;
		return res;
	}
	friend ModInt operator/(const ModInt &lh, const ModInt &rh)
	{
		ModInt res = lh;
		res /= rh;
		return res;
	}
	friend bool operator==(const ModInt &lh, const ModInt &rh) { return lh.v == rh.v; }
	friend bool operator!=(const ModInt &lh, const ModInt &rh) { return lh.v != rh.v; }
	friend std::istream &operator>>(std::istream &is, ModInt &aim)
	{
		ll tmp;
		is >> tmp;
		aim = ModInt(tmp);
		return is;
	}
	friend std::ostream &operator<<(std::ostream &os, const ModInt &aim) { return os << aim.Val(); }

protected:
	ll v;
};
using mint = ModInt<MOD>;