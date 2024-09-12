namespace comp {
	inline namespace utils{
		using point_t = double;
		template<typename T, typename std::enable_if<std::is_floating_point_v<T>, int>::type = 0>
		int sign(T k) {
			//if (std::abs(k) < eps) return 0;
			//return (k > 0) ? 1 : -1;
			return (k > eps) - (k < -eps);
		}
		template<typename T, typename std::enable_if<std::is_integral_v<T>, int>::type = 0>
		int sign(T k) {
			//if (k == 0) return 0;
			//return (k > 0) ? 1 : -1;
			return (k > 0) - (k < 0);
		}
		// 比较lhs和rhs的大小
		template<typename T, typename std::enable_if<std::is_floating_point_v<T>, int>::type = 0>
		int cmp(const T& lhs, const T& rhs) { return sign(lhs - rhs); }
	}

	template<typename T>
	struct vector;

	template<typename T, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
	bool inmid(T k1, T k2, T other) { return sign(k1 - other) * sign(k2 - other) <= 0; }

	// 二维点
	template<typename T, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
	struct point {
		T x, y;
		point(const T& x = {}, const T& y = {}) : x(x), y(y) {}
		auto dis(const point& other) const {
			auto dx = x * 1.0 - other.x, dy = y * 1.0 - other.y;
			return sqrt(dx * dx + dy * dy);
		}

		// 求点所在的象限
		// 极角左闭右开,比如第一象限的定义是极角在[0,pi/2)范围的点
		// 原点在0象限
		auto quadrant() const {
			int xsign = sign(x), ysign = sign(y);
			if (xsign > 0 and ysign >= 0) return 1;
			if (xsign <= 0 and ysign > 0) return 2;
			if (xsign < 0 and ysign <= 0) return 3;
			if (xsign >= 0 and ysign < 0) return 4;
			return 0;
		}

		bool operator == (const point& other) const { return (cmp(x, other.x) == 0) and (cmp(y, other.y) == 0); }

		bool operator<(const point& a) const { if (cmp(x, a.x) <= 0) return cmp(y, a.y) < 0; return cmp(x, a.x) < 0; }

		vector<T> operator - (const point& other) const { return { x - other.x,y - other.y }; }

		point operator - (const vector<T>& other) const { return { x - other.x,y - other.y }; }
		point operator + (const vector<T>& other) const { return { x + other.x,y + other.y }; }
		point& operator -= (const vector<T>& other) { x -= other.x; y -= other.y; return *this; }
		point& operator += (const vector<T>& other) { x += other.x; y += other.y; return *this; }

		friend std::istream& operator >> (std::istream& io, point& other) { return io >> other.x >> other.y; }
		friend std::ostream& operator << (std::ostream& io, const point& other) { return io << other.x << blank << other.y; }
	};

	template<typename T>
	struct vector :point<T> {
		using super = point<T>;
		using super::x, super::y;

		vector(T x = {}, T y = {}) : super(x, y) { }
		vector(const point<T>& tail) : super(tail) { }
		vector(const point<T>& start, const point<T>& tail) : super(tail.x - start.x, tail.y - start.y) { }

		// to-left 测试
		// 1表示当前向量在other逆时针侧
		int toleft(const vector& other) const { const auto t = cross(other); return sign(t); }

		vector& operator += (const vector& other) { x += other.x; y += other.y; return *this; }
		vector& operator -= (const vector& other) { x -= other.x; y -= other.y; return *this; }
		vector operator + (const vector& other) const { return { x + other.x, y + other.y }; }
		vector operator - (const vector& other) const { return { x - other.x, y - other.y }; }

		template<typename Ty, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
		vector& operator /= (const Ty& other) { x /= other; y /= other; return *this; }
		template<typename Ty, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
		vector& operator *= (const Ty& other) { x *= other; y *= other; return *this; }

		template<typename Ty, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
		vector operator * (const Ty& other) const { return { x * other, y * other }; }
		template<typename Ty, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
		vector operator / (const Ty& other) const { return { x / other, y / other }; }

		decltype(auto) dot(const vector& other) const { return x * other.x + y * other.y; }
		decltype(auto) cross(const vector& other) const { return x * other.y - y * other.x; }
		
		friend decltype(auto) dot(const vector& lhs, const vector& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
		friend decltype(auto) cross(const vector& lhs, const vector& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

		// 求极角
		point_t polar() const { return atan2(y, x); }
		// 求二范数/模长
		auto norm2() const { return sqrt(x * x + y * y); }
		auto length() const { return sqrt(x * x + y * y); }
		auto length2() const { return x * x + y * y; }

		vector unit() const {
			auto len = norm2();
			return { x / len,y / len };
		}
		friend int clockwise(const vector& lhs, const vector& rhs) {
			return sign(rhs.cross(lhs)) > 0;
		}

		// 逆时针旋转ang弧度
		void rotate(const point_t& ang) {
			T nx, ny;
			point_t sinv = sin(ang), cosv = cos(ang);
			nx = x * cosv - y * sinv; ny = x * sinv + y * cosv;
			x = nx; y = ny;
		}
		friend vector rotate(const vector& v,const point_t& ang) {
			T nx, ny;    
			point_t sinv = sin(ang), cosv = cos(ang);
			nx = v.x * cosv - v.y * sinv; ny = v.x * sinv + v.y * cosv;
			return { nx,ny };
		}

		// Todo 分解向量
	};

	// 极角排序
	template<typename T, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
	struct argcmp {
		using Point = vector<T>;
		bool operator()(const Point& a, const Point& b) const {
			const auto quad = [](const Point& a) {
					if (a.y < -eps) return 1;
					if (a.y > eps) return 4;
					if (a.x < -eps) return 5;
					if (a.x > eps) return 3;
					return 2;
				};
			const int qa = quad(a), qb = quad(b);
			if (qa != qb) return qa < qb;
			const auto t = a.cross(b);
			// if (abs(t)<=eps) return a*a<b*b-eps;  // 不同长度的向量需要分开
			return t > eps;
		}
	};

	// 直线
	template<typename T, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
	struct line
	{
		point<T> p;
		vector<T> v;  // p 为直线上一点，v 为方向向量

		bool operator==(const line& a) const { return v.toleft(a.v) == 0 && v.toleft(p - a.p) == 0; }
		int toleft(const point<T>& a) const { return v.toleft(a - p); }  // to-left 测试
		bool operator<(const line& a) const  // 半平面交算法定义的排序
		{
			if (std::abs(v.cross(a.v)) <= eps && v.dot(a.v) >= -eps) return toleft(a.p) == -1;
			return argcmp<T>()(v, a.v);
		}

		// 涉及浮点数
		point<T> inter(const line& a) const { return p + v * ((a.v.cross(p - a.p)) / (v.cross(a.v))); }  // 直线交点
		long double dis(const point<T>& a) const { return std::abs(v.cross(a - p)) / v.length(); }  // 点到直线距离
		point<T> proj(const point<T>& a) const { return p + v * ((v * (a - p)) / (v * v)); }  // 点在直线上的投影
	};

	//线段
	template<typename T, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
	struct segment {
		point<T> a, b;

		bool operator<(const segment& s) const { return std::make_pair(a, b) < std::make_pair(s.a, s.b); }

		// 判定性函数建议在整数域使用

		// 判断点是否在线段上
		// -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
		int is_on(const point<T>& p) const {
			if (p == a || p == b) return -1;
			return (p - a).toleft(p - b) == 0 && (p - a).dot(p - b) < -eps;
		}

		// 判断线段直线是否相交
		// -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
		int is_inter(const line<T>& l) const
		{
			if (l.toleft(a) == 0 || l.toleft(b) == 0) return -1;
			return l.toleft(a) != l.toleft(b);
		}

		// 判断两线段是否相交
		// -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
		int is_inter(const segment<T>& s) const
		{
			if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
			const line<T> l{ a,b - a }, ls{ s.a,s.b - s.a };
			return l.toleft(s.a) * l.toleft(s.b) == -1 && ls.toleft(a) * ls.toleft(b) == -1;
		}

		// 点到线段距离
		long double dis(const point<T>& p) const
		{
			if ((p - a).dot(b - a) < -eps || (p - b).dot(a - b) < -eps) return std::min(p.dis(a), p.dis(b));
			const line<T> l{ a,b - a };
			return l.dis(p);
		}

		// 两线段间距离
		long double dis(const segment<T>& s) const
		{
			if (is_inter(s)) return 0;
			return std::min({ dis(s.a),dis(s.b),s.dis(a),s.dis(b) });
		}
	};

	// 多边形(点按照逆时针排序)
	template<typename T, typename std::enable_if<std::is_arithmetic_v<T>, int>::type = 0>
	struct polygon {
		std::vector<point<T>> st;

		using Line = line<T>;

		auto nxt(const size_t i) const { return i == st.size() - 1 ? 0 : i + 1; }
		auto pre(const size_t i) const { return i == 0 ? st.size() - 1 : i - 1; }

		// 回转数
		// 返回值第一项表示点是否在多边形边上
		// 对于狭义多边形，回转数为 0 表示点在多边形外，否则点在多边形内
		std::pair<bool, int> winding(const point<T>& a) const
		{
			int cnt = 0;
			for (size_t i = 0; i < st.size(); i++)
			{
				const point<T> u = st[i], v = st[nxt(i)];
				if (sign((a - u).cross(a - v)) == 0 && (a - u).dot(a - v) <= eps) return { true,0 };
				if (sign(u.y - v.y) == 0) continue;
				const Line uv = { u,v - u };
				if (u.y < v.y - eps && uv.toleft(a) <= 0) continue;
				if (u.y > v.y + eps && uv.toleft(a) >= 0) continue;
				if (u.y < a.y - eps && v.y >= a.y - eps) cnt++;
				if (u.y >= a.y - eps && v.y < a.y - eps) cnt--;
			}
			return { false,cnt };
		}
	};

	using Vec = vector<point_t>;
	using Point = point<point_t>;

}