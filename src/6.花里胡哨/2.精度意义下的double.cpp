class podouble {
protected:
	double v;
	static constexpr bool is_zero(const double& val) { return val > negeps && val < eps; }
	static constexpr bool not_zero(const double& val) { return val <= negeps || val >= eps; }
public:
	podouble() = default;
	constexpr podouble(const double& rhs) : v(rhs) { };
	constexpr decltype(auto) operator ++ () { return ++v; }
	constexpr decltype(auto) operator -- () { return --v; }
	constexpr decltype(auto) operator ++ (int) { return v++; }
	constexpr decltype(auto) operator -- (int) { return v--; }
	friend decltype(auto) operator >> (std::istream& in, podouble& v) { in >> v.v; return (in); }
	friend decltype(auto) operator << (std::ostream& out, podouble& v) { out << v.v; return (out); }
	friend constexpr decltype(auto) operator += (podouble& lhs, const podouble& rhs) { lhs.v += rhs.v; return (lhs); }
	friend constexpr decltype(auto) operator -= (podouble& lhs, const podouble& rhs) { lhs.v -= rhs.v; return (lhs); }
	friend constexpr decltype(auto) operator *= (podouble& lhs, const podouble& rhs) { lhs.v *= rhs.v; return (lhs); }
	friend constexpr decltype(auto) operator /= (podouble& lhs, const podouble& rhs) { lhs.v /= rhs.v; return (lhs); }
	friend constexpr decltype(auto) operator + (const podouble& lhs, const podouble& rhs) { return podouble(lhs.v+rhs.v); }
	friend constexpr decltype(auto) operator - (const podouble& lhs, const podouble& rhs) { return podouble(lhs.v-rhs.v); }
	friend constexpr decltype(auto) operator * (const podouble& lhs, const podouble& rhs) { return podouble(lhs.v*rhs.v); }
	friend constexpr decltype(auto) operator / (const podouble& lhs, const podouble& rhs) { return podouble(lhs.v/rhs.v); }
	friend constexpr decltype(auto) operator >  (const podouble& lhs, const podouble& rhs) { return (lhs.v - rhs.v > eps); }
	friend constexpr decltype(auto) operator >= (const podouble& lhs, const podouble& rhs) { return (lhs.v - rhs.v >= eps); }
	friend constexpr decltype(auto) operator <  (const podouble& lhs, const podouble& rhs) { return (lhs.v - rhs.v < negeps); }
	friend constexpr decltype(auto) operator <= (const podouble& lhs, const podouble& rhs) { return (lhs.v - rhs.v <= negeps); }
	friend constexpr decltype(auto) operator == (const podouble& lhs, const podouble& rhs) { return (is_zero(lhs.v - rhs.v)); }
	friend constexpr decltype(auto) operator != (const podouble& lhs, const podouble& rhs) { return (not_zero(lhs.v - rhs.v)); }
};
using doublev = podouble;