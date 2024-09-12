struct Point
{
	ll x, y;
	ll Det(const Point &rh) const { return x * rh.y - y * rh.x; }
	ll Dot(const Point &rh) const { return x * rh.x + y * rh.y; }
	Point operator-(const Point &rh) const { return {x - rh.x, y - rh.y}; }
	bool InLine(const Point &a, const Point &b) const { return ((*this - a).Det(*this - b) == 0 and (*this - a).Dot(*this - b) <= 0); }
	friend std::istream &operator>>(std::istream &is, Point &aim)
	{
		is >> aim.x >> aim.y;
		return is;
	}
};