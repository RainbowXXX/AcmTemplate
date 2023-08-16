struct ComplexClass {
	ll x, y;
	ComplexClass(ll _ = 0, ll __ = 0) { x = _; y = __; }
	void out() { }
	ll abs() { return x * x + y * y; }
	ComplexClass con() { return ComplexClass(x, -y); }
	bool operator ==(const ComplexClass& B) const { return x == B.x && y == B.y; }
	ComplexClass operator + (const ComplexClass& B) const { return ComplexClass(x + B.x, y + B.y); }
	ComplexClass operator - (const ComplexClass& B) const { return ComplexClass(x - B.x, y - B.y); }
	ComplexClass operator * (const ComplexClass& B) const { return ComplexClass(1 * x * B.x - 1 * y * B.y, 1 * x * B.y + 1 * y * B.x); }
	static ll dr(ll A, ll B) { ll x = (A > 0 ? A : -A), ret = x / B; if ((x % B) * 2 > B) ret++; return (A > 0 ? ret : -ret); }
	ComplexClass operator / (ComplexClass& B) const { ll mb = B.abs(); return ComplexClass(dr(x * B.x + y * B.y, mb), dr(y * B.x - x * B.y, mb)); }
	ComplexClass operator %(ComplexClass B) { return (*this) - ((*this) / B * B); }
};
ComplexClass gcd(ComplexClass A, ComplexClass B) {
	if (B == ComplexClass(0, 0)) return A;
	return gcd(B, A % B);
}