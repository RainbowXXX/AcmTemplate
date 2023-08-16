struct Vector2;
struct Coord2 {
	double x, y;
	Vector2 operator >> (const Coord2&);
	Coord2(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	Coord2 operator + (const Coord2& rhs) { return Coord2(rhs.x + x, rhs.y + y); }
	Coord2 operator - (const Coord2& rhs) { return Coord2(rhs.x - x, rhs.y - y); }
};
struct Vector2 {
	double x, y;
	Vector2(double _x, double _y) : x(_x), y(_y) {}
	Vector2(const Coord2& rhs) : x(rhs.x), y(rhs.y) {}
	Vector2(const Coord2& lhs, const Coord2& rhs) : x(rhs.x - lhs.x), y(rhs.y - lhs.y) {}
	friend double abs(const Vector2& rhs) { return sqrt(rhs.x * rhs.x + rhs.y * rhs.y); }
	friend constexpr double cross(const Vector2& lhs, const Vector2& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }
	friend constexpr double operator * (const Vector2& lhs, const Vector2& rhs) { return rhs.x * lhs.x + rhs.y * lhs.y; }
	friend Vector2 operator + (const Vector2& lhs, const Vector2& rhs) { return Vector2(rhs.x + lhs.x, rhs.y + lhs.y); }
	friend Vector2 operator - (const Vector2& lhs, const Vector2& rhs) { return Vector2(rhs.x - lhs.x, rhs.y - lhs.y); }
	// 叉积
	double cross(const Vector2& rhs) { return x * rhs.y - y * rhs.x; }
	// 旋转(弧度制)
	Vector2 rotate(double angle) { return Vector2(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)); }
	// 投影
	double proj(const Vector2& rhs) { return (*this) * rhs / abs(rhs); }
	// 分解
	void decompose(const Vector2& lhs, const Vector2& rhs, double& ratio1, double& ratio2) {
		double length = sqrt(lhs.x * lhs.x + lhs.y * lhs.y); ratio1 = (*this) * lhs / length;
		length = sqrt(rhs.x * rhs.x + rhs.y * rhs.y); ratio2 = (*this) * rhs / length;
	}
};
// 两个坐标形成向量
Vector2 Coord2::operator >> (const Coord2& rhs) { return Vector2(rhs.x - x, rhs.y - y); }