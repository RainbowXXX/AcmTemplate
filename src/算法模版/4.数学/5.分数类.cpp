struct Fraction
{
public:
	Fraction(ll fz = 0, ll fm = 1, int fh = 1) {
		_sym = fh; _rator = fz; _nator = fm;
		Norm();
	}
	inline void Norm(void)
	{
		if (_rator == 0) {
			_sym = 1; _nator = 1;
			return;
		}
		if (_rator < 0) {
			_sym *= -1; _rator *= -1;
		}
		if (_nator < 0) {
			_sym *= -1; _rator *= -1;
		}
		ll gcd = _gcd(_rator, _nator);
		_rator /= gcd; _nator /= gcd;
		return;
	}
	void Init(ll fz, ll fm) {
		_sym = 1; _rator = fz; _nator = fm; Norm();
		return;
	}
	int fh() const { return _sym; }
	ll fz() const { return _rator; }
	ll fm() const { return _nator; }
	Fraction& operator++() {
		_rator *= _sym; _sym = 1; _rator += _nator; Norm();
		return *this;
	}
	Fraction& operator--() {
		_rator *= _sym; _sym = 1; _rator -= _nator; Norm();
		return *this;
	}
	Fraction operator++(int) {
		Fraction oldVal = *this; ++* this;
		return oldVal;
	}
	Fraction operator--(int) {
		Fraction oldVal = *this; --* this;
		return oldVal;
	}
	Fraction& operator+=(const Fraction& rhs) {
		ll fm = _lcm(_nator, rhs._nator);
		ll fz = fm / _nator * _rator * _sym + fm / rhs._nator * rhs._rator * rhs._sym;
		_sym = 1; _rator = fz; _nator = fm; Norm();
		return *this;
	}
	Fraction& operator-=(const Fraction& rhs) {
		ll fm = _lcm(_nator, rhs._nator);
		ll fz = fm / _nator * _rator * _sym - fm / rhs._nator * rhs._rator * rhs._sym;
		_sym = 1; _rator = fz; _nator = fm; Norm();
		return *this;
	}
	Fraction& operator*=(const Fraction& rhs) {
		_sym *= rhs._sym; _rator *= rhs._rator; _nator *= rhs._nator; Norm();
		return *this;
	}
	Fraction& operator/=(const Fraction& rhs) { return *this *= rhs.inv(); }
	Fraction operator+() const { return *this; }
	Fraction operator-() const
	{
		Fraction res;
		res._sym = _sym * -1; res._rator = _rator; res._nator = _nator;
		return res;
	}
	Fraction pow(long long exp) const
	{
		assert(exp >= 0);
		Fraction res;
		Fraction base = *this;
		res.Init(1, 1);
		while (exp) {
			if (exp & 1) res *= base;
			base *= base; exp >>= 1;
		}
		return res;
	}
	Fraction inv() const
	{
		// assert(_v);
		Fraction res;
		res._sym = _sym; res._rator = _nator; res._nator = _rator;
		return res;
	}
	friend Fraction operator+(const Fraction& lhs, const Fraction& rhs)
	{
		Fraction res = lhs; res += rhs;
		return res;
	}
	friend Fraction operator-(const Fraction& lhs, const Fraction& rhs)
	{
		Fraction res = lhs; res -= rhs;
		return res;
	}
	friend Fraction operator*(const Fraction& lhs, const Fraction& rhs)
	{
		Fraction res = lhs; res *= rhs;
		return res;
	}
	friend Fraction operator/(const Fraction& lhs, const Fraction& rhs)
	{
		Fraction res = lhs; res /= rhs;
		return res;
	}
	friend bool operator==(const Fraction& lhs, const Fraction& rhs) { return (lhs._sym == rhs._sym && lhs._rator == rhs._rator && lhs._nator == rhs._nator); }
	friend bool operator!=(const Fraction& lhs, const Fraction& rhs) { return (lhs._sym != rhs._sym || lhs._rator != rhs._sym || lhs._nator != rhs._nator); }
	friend bool operator<(const Fraction& lhs, const Fraction& rhs)
	{
		if (lhs._sym != rhs._sym) return lhs._sym < rhs._sym;
		ll lcm = _lcm(lhs._nator, rhs._nator);
		ll lv = lcm / lhs._nator;
		ll rv = lcm / rhs._nator;
		lv *= lhs._rator * lhs._sym;
		rv *= rhs._rator * rhs._sym;
		return lv < rv;
	}
	friend bool operator<=(const Fraction& lhs, const Fraction& rhs)
	{
		if (lhs._sym != rhs._sym) return lhs._sym <= rhs._sym;
		ll lcm = _lcm(lhs._nator, rhs._nator);
		ll lv = lcm / lhs._nator;
		ll rv = lcm / rhs._nator;
		lv *= lhs._rator * lhs._sym;
		rv *= rhs._rator * rhs._sym;
		return lv <= rv;
	}
	friend bool operator>(const Fraction& lhs, const Fraction& rhs)
	{
		if (lhs._sym != rhs._sym) return lhs._sym > rhs._sym;
		ll lcm = _lcm(lhs._nator, rhs._nator);
		ll lv = lcm / lhs._nator;
		ll rv = lcm / rhs._nator;
		lv *= lhs._rator * lhs._sym;
		rv *= rhs._rator * rhs._sym;
		return lv > rv;
	}
	friend bool operator>=(const Fraction& lhs, const Fraction& rhs)
	{
		if (lhs._sym != rhs._sym) return lhs._sym >= rhs._sym;
		ll lcm = _lcm(lhs._nator, rhs._nator);
		ll lv = lcm / lhs._nator;
		ll rv = lcm / rhs._nator;
		lv *= lhs._rator * lhs._sym;
		rv *= rhs._rator * rhs._sym;
		return lv >= rv;
	}
	friend std::istream& operator>>(std::istream& is, Fraction& aim)
	{
		ll fz, fm;
		is >> fz >> fm; aim.Init(fz, fm);
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const Fraction& aim) { return os << aim.fh() * aim.fz() << '/' << aim.fm(); }

private:
	int _sym;
	ll _rator, _nator;
};