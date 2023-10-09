// 计算几何(摘自吉如一)
namespace comp {
	int sign(double k) {
		//if (k > eps) return 1;
		//if (k < -eps) return -1;
		//return 0;

		if (fabs(k) < eps)
			return 0;
		return (k > 0) ? 1 : -1;
	}
	int cmp(double k1, double k2) { return sign(k1 - k2); }
	bool inmid(double k1, double k2, double other) { return sign(k1 - other) * sign(k2 - other) <= 0; }

	struct point {
		double x, y;

		point operator+(const point& k1) const { return point{ k1.x + x, k1.y + y }; }

		point operator-(const point& k1) const { return point{ x - k1.x, y - k1.y }; }

		point operator*(double k1) const { return point{ x * k1, y * k1 }; }

		point operator/(double k1) const { return point{ x / k1, y / k1 }; }

		int operator==(const point& k1) const { return cmp(x, k1.x) == 0 && cmp(y, k1.y) == 0; }

		point turn(double k1) { return point{ x * cos(k1) - y * sin(k1), x * sin(k1) + y * cos(k1) }; }

		point turn90() { return point{ -y, x }; }

		bool operator<(const point& k1) const {
			int a = cmp(x, k1.x);
			if (a == -1) return 1; else if (a == 1) return 0; else return cmp(y, k1.y) == -1;
		}

		double abs() const { return sqrt(x * x + y * y); }

		double abs2() const { return x * x + y * y; }

		double dis(const point& k1) { return ((*this) - k1).abs(); }

		// 单位化
		point unit() const {
			double w = abs();
			return point{ x / w, y / w };
		}

		friend std::istream& operator>>(std::istream& io, point& other) {
			io >> other.x >> other.y;
			return io;
		}

		friend std::ostream& operator<<(std::ostream& io, const point& other) {
			io << other.x << blank << other.y;
			return io;
		}

		// 获取极角
		double getw() const { return atan2(y, x); }

		point getdel() {
			if (sign(x) == -1 || (sign(x) == 0 && sign(y) == -1))
				return (*this) * (-1);
			else return (*this);
		}

		int getP() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) == -1); }
	};

	double cross(point k1, point k2) { return k1.x * k2.y - k1.y * k2.x; }
	double dot(point k1, point k2) { return k1.x * k2.x + k1.y * k2.y; }

	struct circle {
		point o;
		double r;

		int inside(point k) { return cmp(r, o.dis(k)); }
	};

	// 有向直线,方向为p[0] -> p[1]
	struct line {

		point p[2];

		line(point k1, point k2) {
			p[0] = k1;
			p[1] = k2;
		}

		point& operator[](int k) { return p[k]; }

		// 判断一个点是否在直线中?
		int include(point k) { return sign(cross(p[1] - p[0], k - p[0])) > 0; }

		// 取直线方向,方向为p[0] -> p[1]
		point dir() { return p[1] - p[0]; }

		line push() {
			const double eps = 1e-6;
			point delta = (p[1] - p[0]).turn90().unit() * eps;
			return { p[0] - delta, p[1] - delta };
		}
	};

	bool inmid(point k1, point k2, point other) { return inmid(k1.x, k2.x, other.x) and inmid(k1.y, k2.y, other.y); }

	// 两个向量的夹角
	double rad(point k1, point k2) { return atan2(cross(k1, k2), dot(k1, k2)); }

	// 比较极角
	bool compareangle(point k1, point k2) {
		return k1.getP() < k2.getP() || (k1.getP() == k2.getP() && sign(cross(k1, k2)) > 0);
	}

	// aq在ab上投影的点坐标
	point proj(point a, point b, point q) {
		point k = b - a;
		return a + k * (dot(q - a, k) / k.abs2());
	}

	// q关于ab的对称坐标
	point reflect(point a, point b, point q) { return proj(a, b, q) * 2 - q; }

	// oa是否在ob的顺时针方向
	int clockwise(point o, point a, point b) {
		return sign(cross(a - o, b - o));
	}

	// ab是否与cd相交
	int checkLL(point a, point b, point c, point d) {
		return cmp(cross(c - a, d - a), cross(c - b, d - b)) != 0;
	}

	// 计算ab与cd的交点
	point getLL(point a, point b, point c, point d) {
		double w1 = cross(a - c, d - c), w2 = cross(d - c, b - c);
		return (a * w2 + b * w1) / (w1 + w2);
	}

	// [l1,r1]与[l2,r2]是否相交
	int intersect(double l1, double r1, double l2, double r2) {
		if (l1 > r1) std::swap(l1, r1);
		if (l2 > r2) std::swap(l2, r2);
		return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
	}

	// 线段ab与线段cd是否相交
	int checkSS(point a, point b, point c, point d) {
		return intersect(a.x, b.x, c.x, d.x) && intersect(a.y, b.y, c.y, d.y) &&
			sign(cross(c - a, d - a)) * sign(cross(c - b, d - b)) <= 0 &&
			sign(cross(a - c, b - c)) * sign(cross(a - d, b - d)) <= 0;
	}

	// 点p与线段ab的最小距离
	double disSP(point a, point b, point q) {
		//point k3 = proj(a, b, q);
		//if (inmid(a, b, k3)) return q.dis(k3); else return std::min(q.dis(a), q.dis(b));
		if (a == b) return (q - a).abs();
		point v1 = b - a, v2 = q - a, v3 = q - b;
		if (sign(dot(v1, v2)) < 0) return v2.abs();
		else if (sign(dot(v1, v3)) > 0) return v3.abs();
		return fabs(cross(v1, v2)) / v1.abs();
	}

	// 线段ab与线段cd的最小距离
	double disSS(point a, point b, point c, point d) {
		if (checkSS(a, b, c, d)) return 0;
		else
			return std::min(std::min(disSP(a, b, c), disSP(a, b, d)),
				std::min(disSP(c, d, a), disSP(c, d, b)));
	}

	// 判断p是否在线段ab上
	int onS(point a, point b, point q) { return inmid(a, b, q) && sign(cross(a - q, b - a)) == 0; }

	// 获取两条直线的交点
	point getLL(line k1, line k2) { return getLL(k1[0], k1[1], k2[0], k2[1]); }

	// 两条直线是否平行
	int parallel(line k1, line k2) { return sign(cross(k1.dir(), k2.dir())) == 0; }

	// 判断两条直线的方向是否相似(即方向夹角为锐角)
	int sameDir(line k1, line k2) { return (parallel(k1, k2) != 0) and (sign(dot(k1.dir(), k2.dir())) == 1); }

	int operator<(line k1, line k2) {
		if (sameDir(k1, k2)) return k2.include(k1[0]);
		return compareangle(k1.dir(), k2.dir());
	}

	// 检查k3是否包含k1和k2的交点
	int checkpos(line k1, line k2, line k3) { return k3.include(getLL(k1, k2)); }

	// 找到一堆直线的半平面交
	std::vector<line> getHL(std::vector<line>& L) {
		std::deque<line> q;
		std::sort(L.begin(), L.end());
		for (int i = 0; i < (int)L.size(); i++) {
			if (i && sameDir(L[i], L[i - 1])) continue;
			while (q.size() > 1 && !checkpos(q[q.size() - 2], q[q.size() - 1], L[i])) q.pop_back();
			while (q.size() > 1 && !checkpos(q[1], q[0], L[i])) q.pop_front();
			q.push_back(L[i]);
		}
		while (q.size() > 2 && !checkpos(q[q.size() - 2], q[q.size() - 1], q[0])) q.pop_back();
		while (q.size() > 2 && !checkpos(q[1], q[0], q[q.size() - 1])) q.pop_front();
		std::vector<line> ans;
		for (int i = 0; i < q.size(); i++) ans.push_back(q[i]);
		return ans;
	}

	// 点集中最近点的距离
	double closepoint(std::vector<point>& A, int l, int r) {
		if (r - l <= 5) {
			double ans = 1e20;
			for (int i = l; i <= r; i++) for (int j = i + 1; j <= r; j++) ans = std::min(ans, A[i].dis(A[j]));
			return ans;
		}
		int mid = (l + r) >> 1;
		double ans = std::min(closepoint(A, l, mid), closepoint(A, mid + 1, r));
		std::vector<point> B;
		for (int i = l; i <= r; i++) if (abs(A[i].x - A[mid].x) <= ans) B.push_back(A[i]);
		std::sort(B.begin(), B.end(), [](point k1, point k2) { return k1.y < k2.y; });
		for (int i = 0; i < B.size(); i++)
			for (int j = i + 1; j < B.size() && B[j].y - B[i].y < ans; j++)
				ans = std::min(ans, B[i].dis(B[j]));
		return ans;
	}

	// 获取两个圆的位置, 返回值(0:包含,1:内切,2:相交,3:外切,4:相离)
	int checkposCC(circle k1, circle k2) {
		if (cmp(k1.r, k2.r) == -1) std::swap(k1, k2);
		double dis = k1.o.dis(k2.o);
		int w1 = cmp(dis, k1.r + k2.r), w2 = cmp(dis, k1.r - k2.r);
		if (w1 > 0) return 4;
		else if (w1 == 0) return 3;
		else if (w2 > 0) return 2;
		else if (w2 == 0) return 1; else return 0;
	}

	// 获取圆和直线的交点
	std::vector<point> getCL(circle k1, point k2, point k3) {
		point k = proj(k2, k3, k1.o);
		double d = k1.r * k1.r - (k - k1.o).abs2();
		if (sign(d) == -1) return {};
		point del = (k3 - k2).unit() * std::sqrt(std::max((double)0.0, d));
		return { k - del, k + del };
	}

	// 获取圆和圆的交点
	std::vector<point> getCC(circle k1, circle k2) {
		int pd = checkposCC(k1, k2);
		if (pd == 0 || pd == 4) return {};
		double a = (k2.o - k1.o).abs2(), cosA =
			(k1.r * k1.r + a - k2.r * k2.r) / (2 * k1.r * sqrt(std::max(a, (double)0.0)));
		double b = k1.r * cosA, c = std::sqrt(std::max((double)0.0, k1.r * k1.r - b * b));
		point k = (k2.o - k1.o).unit(), m = k1.o + k * b, del = k.turn90() * c;
		return { m - del, m + del };
	}

	// 获取过一点的圆的切线
	std::vector<point> TangentCP(circle k1, point k2) {
		double a = (k2 - k1.o).abs(), b = k1.r * k1.r / a, c = sqrt(std::max((double)0.0, k1.r * k1.r - b * b));
		point k = (k2 - k1.o).unit(), m = k1.o + k * b, del = k.turn90() * c;
		return { m - del, m + del };
	}

	// 获取两个圆的外公切线
	std::vector<line> TangentoutCC(circle k1, circle k2) {
		int pd = checkposCC(k1, k2);
		if (pd == 0) return {};
		if (pd == 1) {
			point k = getCC(k1, k2)[0];
			return { line{k, k} };
		}
		if (cmp(k1.r, k2.r) == 0) {
			point del = (k2.o - k1.o).unit().turn90().getdel();
			return { line{k1.o - del * k1.r, k2.o - del * k2.r}, line{k1.o + del * k1.r, k2.o + del * k2.r} };
		}
		else {
			point p = (k2.o * k1.r - k1.o * k2.r) / (k1.r - k2.r);
			std::vector<point> A = TangentCP(k1, p), B = TangentCP(k2, p);
			std::vector<line> ans;
			for (int i = 0; i < A.size(); i++) ans.emplace_back(A[i], B[i]);
			return ans;
		}
	}

	// 获取两个圆的内公切线
	std::vector<line> TangentinCC(circle k1, circle k2) {
		int pd = checkposCC(k1, k2);
		if (pd <= 2) return {};
		if (pd == 3) {
			point k = getCC(k1, k2)[0];
			return { line{k, k} };
		}
		point p = (k2.o * k1.r + k1.o * k2.r) / (k1.r + k2.r);
		std::vector<point> A = TangentCP(k1, p), B = TangentCP(k2, p);
		std::vector<line> ans;
		for (int i = 0; i < A.size(); i++) ans.emplace_back(A[i], B[i]);
		return ans;
	}

	// 获取两个圆的公切线(包含外切线和内切线)
	std::vector<line> TangentCC(circle k1, circle k2) {
		int flag = 0;
		if (k1.r < k2.r) std::swap(k1, k2), flag = 1;
		std::vector<line> A = TangentoutCC(k1, k2), B = TangentinCC(k1, k2);
		for (const line& k : B) A.push_back(k);
		if (flag) for (line& k : A) std::swap(k[0], k[1]);
		return A;
	}

	double getarea(circle k1, point k2, point k3) {

		point k = k1.o;
		k1.o = k1.o - k;
		k2 = k2 - k;
		k3 = k3 - k;
		int pd1 = k1.inside(k2), pd2 = k1.inside(k3);
		std::vector<point> A = getCL(k1, k2, k3);
		if (pd1 >= 0) {
			if (pd2 >= 0) return cross(k2, k3) / 2;
			return k1.r * k1.r * rad(A[1], k3) / 2 + cross(k2, A[1]) / 2;
		}
		else if (pd2 >= 0) {
			return k1.r * k1.r * rad(k2, A[0]) / 2 + cross(A[0], k3) / 2;
		}
		else {
			int pd = cmp(k1.r, disSP(k2, k3, k1.o));
			if (pd <= 0) return k1.r * k1.r * rad(k2, k3) / 2;
			return cross(A[0], A[1]) / 2 + k1.r * k1.r * (rad(k2, A[0]) + rad(A[1], k3)) / 2;
		}
	}

	// 使用三个点构造圆
	circle getcircle(point k1, point k2, point k3) {
		double a1 = k2.x - k1.x, b1 = k2.y - k1.y, c1 = (a1 * a1 + b1 * b1) / 2;
		double a2 = k3.x - k1.x, b2 = k3.y - k1.y, c2 = (a2 * a2 + b2 * b2) / 2;
		double d = a1 * b2 - a2 * b1;
		point o = point{ k1.x + (c1 * b2 - c2 * b1) / d, k1.y + (a1 * c2 - a2 * c1) / d };
		return circle{ o, k1.dis(o) };
	}

	// 获取最小的圆
	circle getScircle(std::vector<point> A) {
		std::mt19937 rnd;
		std::shuffle(A.begin(), A.end(), rnd);
		//random_shuffle(A.begin(), A.end());
		circle ans = circle{ A[0], 0 };
		for (int i = 1; i < A.size(); i++)
			if (ans.inside(A[i]) == -1) {
				ans = circle{ A[i], 0 };
				for (int j = 0; j < i; j++)
					if (ans.inside(A[j]) == -1) {
						ans.o = (A[i] + A[j]) / 2;
						ans.r = ans.o.dis(A[i]);
						for (int k = 0; k < j; k++)
							if (ans.inside(A[k]) == -1)
								ans = getcircle(A[i], A[j], A[k]);
					}
			}
		return ans;
	}

	double area(std::vector<point> A) {
		double ans = 0;
		for (int i = 0; i < A.size(); i++) ans += cross(A[i], A[(i + 1) % A.size()]);
		return ans / 2;
	}

	// 判断点集是否为凸包
	int checkconvex(std::vector<point> A) {
		size_t n = A.size();
		A.push_back(A[0]);
		A.push_back(A[1]);
		for (int i = 0; i < n; i++) if (sign(cross(A[i + 1] - A[i], A[i + 2] - A[i])) == -1) return 0;
		return 1;
	}

	// 判断点q是否在A围成的多边形中?
	int contain(std::vector<point> A, point q) {
		int pd = 0;
		A.push_back(A[0]);
		for (int i = 1; i < A.size(); i++) {
			point u = A[i - 1], v = A[i];
			if (onS(u, v, q)) return 1;
			if (cmp(u.y, v.y) > 0) std::swap(u, v);
			if (cmp(u.y, q.y) >= 0 || cmp(v.y, q.y) < 0) continue;
			if (sign(cross(u - v, q - v)) < 0) pd ^= 1;
		}
		return pd << 1;
	}

	// flag代表是否取三点共线, 默认不取
	std::vector<point> ConvexHull(std::vector<point> A, int flag = 1) {
		size_t n = A.size();
		std::vector<point> ans(n * 2);
		sort(A.begin(), A.end());
		int now = -1;
		for (int i = 0; i < A.size(); i++) {
			while (now > 0 && sign(cross(ans[now] - ans[now - 1], A[i] - ans[now - 1])) < flag) now--;
			ans[++now] = A[i];
		}
		int pre = now;
		for (size_t i = n - 2; i != (size_t)-1; i--) {
			while (now > pre && sign(cross(ans[now] - ans[now - 1], A[i] - ans[now - 1])) < flag) now--;
			ans[++now] = A[i];
		}
		ans.resize(now);
		return ans;
	}

	double convexDiameter(std::vector<point> A) {
		size_t now = 0, n = A.size();
		double ans = 0;
		for (size_t i = 0; i < A.size(); i++) {
			now = std::max(now, i);
			while (1) {
				double k1 = A[i].dis(A[now % n]), k2 = A[i].dis(A[(now + 1) % n]);
				ans = std::max(ans, std::max(k1, k2));
				if (k2 > k1) now++; else break;
			}
		}
		return ans;
	}

	std::vector<point> convexcut(std::vector<point> A, point k1, point k2) {

		size_t n = A.size();
		A.push_back(A[0]);
		std::vector<point> ans;
		for (int i = 0; i < n; i++) {
			int w1 = clockwise(k1, k2, A[i]), w2 = clockwise(k1, k2, A[i + 1]);
			if (w1 >= 0) ans.push_back(A[i]);
			if (w1 * w2 < 0) ans.push_back(getLL(k1, k2, A[i], A[i + 1]));
		}
		return ans;
	}

	int checkPoS(std::vector<point> A, point k1, point k2) {

		struct ins {
			point m, u, v;

			int operator<(const ins& k) const { return m < k.m; }
		};
		std::vector<ins> B;

		std::vector<point> poly = A;
		A.push_back(A[0]);
		for (int i = 1; i < A.size(); i++)
			if (checkLL(A[i - 1], A[i], k1, k2)) {
				point m = getLL(A[i - 1], A[i], k1, k2);
				if (inmid(A[i - 1], A[i], m)) B.push_back(ins{ m, A[i - 1], A[i] });
			}
		if (B.size() == 0) return 0;
		std::sort(B.begin(), B.end());
		int now = 1;
		while (now < B.size() && B[now].m == B[0].m) now++;
		if (now == B.size()) return 0;
		int flag = contain(poly, (B[0].m + B[now].m) / 2);
		if (flag == 2) return 1;
		point d = B[now].m - B[0].m;
		for (int i = now; i < B.size(); i++) {
			if (!(B[i].m == B[i - 1].m) && flag == 2) return 1;
			int tag = sign(cross(B[i].v - B[i].u, B[i].m + d - B[i].u));
			if (B[i].m == B[i].u || B[i].m == B[i].v) flag += tag; else flag += tag * 2;
		}

		return flag == 2;
	}

	int checkinp(point r, point l, point m) {
		if (compareangle(l, r)) { return compareangle(l, m) && compareangle(m, r); }
		return compareangle(l, m) || compareangle(m, r);
	}

	int checkPosFast(std::vector<point> A, point k1, point k2) {
		if (contain(A, k1) == 2 || contain(A, k2) == 2) return 1;
		if (k1 == k2) return 0;
		A.push_back(A[0]);
		A.push_back(A[1]);
		for (int i = 1; i + 1 < A.size(); i++)
			if (checkLL(A[i - 1], A[i], k1, k2)) {
				point now = getLL(A[i - 1], A[i], k1, k2);
				if (inmid(A[i - 1], A[i], now) == 0 || inmid(k1, k2, now) == 0) continue;
				if (now == A[i]) {
					if (A[i] == k2) continue;
					point pre = A[i - 1], ne = A[i + 1];
					if (checkinp(pre - now, ne - now, k2 - now)) return 1;
				}
				else if (now == k1) {
					if (k1 == A[i - 1] || k1 == A[i]) continue;
					if (checkinp(A[i - 1] - k1, A[i] - k1, k2 - k1)) return 1;
				}
				else if (now == k2 || now == A[i - 1]) continue;
				else return 1;
			}
		return 0;
	}


	void getUDP(std::vector<point> A, std::vector<point>& U, std::vector<point>& D) {
		double l = 1e100, r = -1e100;
		for (int i = 0; i < A.size(); i++) l = std::min(l, A[i].x), r = std::max(r, A[i].x);
		size_t wherel = 0, wherer = 0;
		for (int i = 0; i < A.size(); i++) if (cmp(A[i].x, l) == 0) wherel = i;
		for (size_t i = A.size(); i; i--) if (cmp(A[i - 1].x, r) == 0) wherer = i - 1;
		U.clear();
		D.clear();
		size_t now = wherel;
		while (1) {
			D.push_back(A[now]);
			if (now == wherer) break;
			now++;
			if (now >= A.size()) now = 0;
		}
		now = wherel;
		while (1) {
			U.push_back(A[now]);
			if (now == wherer) break;
			now--;
			if (now < 0) now = A.size() - 1;
		}
	}

	int containCoP(const std::vector<point>& U, const std::vector<point>& D, point k) {
		double lx = U[0].x, rx = U[U.size() - 1].x;
		if (k == U[0] || k == U[U.size() - 1]) return 1;
		if (cmp(k.x, lx) == -1 || cmp(k.x, rx) == 1) return 0;
		size_t where1 = std::lower_bound(U.begin(), U.end(), point{ k.x, -1e100 }) - U.begin();
		size_t where2 = std::lower_bound(D.begin(), D.end(), point{ k.x, -1e100 }) - D.begin();
		int w1 = clockwise(U[where1 - 1], U[where1], k), w2 = clockwise(D[where2 - 1], D[where2], k);
		if (w1 == 1 || w2 == -1) return 0; else if (w1 == 0 || w2 == 0) return 1;
		return 2;
	}

	std::pair<point, point> getTangentCow(const std::vector<point>& U, const std::vector<point>& D, point d) {
		if (sign(d.x) < 0 || (sign(d.x) == 0 && sign(d.y) < 0)) d = d * (-1);
		point whereU, whereD;
		if (sign(d.x) == 0) return std::make_pair(U[0], U[U.size() - 1]);
		size_t l = 0, r = U.size() - 1, ans = 0;
		while (l < r) {
			size_t mid = (l + r) >> 1;
			if (sign(cross(U[mid + 1] - U[mid], d)) <= 0) l = mid + 1, ans = mid + 1; else r = mid;
		}
		whereU = U[ans];
		l = 0, r = D.size() - 1, ans = 0;
		while (l < r) {
			size_t mid = (l + r) >> 1;
			if (sign(cross(D[mid + 1] - D[mid], d)) >= 0) l = mid + 1, ans = mid + 1; else r = mid;
		}
		whereD = D[ans];
		return std::make_pair(whereU, whereD);
	}

	std::pair<point, point> getTangentCoP(const std::vector<point>& U, const std::vector<point>& D, point k) {
		double lx = U[0].x, rx = U[U.size() - 1].x;
		if (k.x < lx) {
			size_t l = 0, r = U.size() - 1, ans = U.size() - 1;
			while (l < r) {
				size_t mid = (l + r) >> 1;
				if (clockwise(k, U[mid], U[mid + 1]) == 1) l = mid + 1; else ans = mid, r = mid;
			}
			point w1 = U[ans];
			l = 0, r = D.size() - 1, ans = D.size() - 1;
			while (l < r) {
				size_t mid = (l + r) >> 1;
				if (clockwise(k, D[mid], D[mid + 1]) == -1) l = mid + 1; else ans = mid, r = mid;
			}
			point w2 = D[ans];
			return std::make_pair(w1, w2);
		}
		else if (k.x > rx) {
			size_t l = 1, r = U.size(), ans = 0;
			while (l < r) {
				size_t mid = (l + r) >> 1;
				if (clockwise(k, U[mid], U[mid - 1]) == -1) r = mid; else ans = mid, l = mid + 1;
			}
			point w1 = U[ans];
			l = 1, r = D.size(), ans = 0;
			while (l < r) {
				size_t mid = (l + r) >> 1;
				if (clockwise(k, D[mid], D[mid - 1]) == 1) r = mid; else ans = mid, l = mid + 1;
			}
			point w2 = D[ans];
			return std::make_pair(w2, w1);
		}
		else {
			size_t where1 = lower_bound(U.begin(), U.end(), point{ k.x, -1e100 }) - U.begin();
			size_t where2 = lower_bound(D.begin(), D.end(), point{ k.x, -1e100 }) - D.begin();
			if ((k.x == lx && k.y > U[0].y) || (where1 && clockwise(U[where1 - 1], U[where1], k) == 1)) {
				size_t l = 1, r = where1 + 1, ans = 0;
				while (l < r) {
					size_t mid = (l + r) >> 1;
					if (clockwise(k, U[mid], U[mid - 1]) == 1) ans = mid, l = mid + 1; else r = mid;
				}
				point w1 = U[ans];
				l = where1, r = U.size() - 1, ans = U.size() - 1;
				while (l < r) {
					size_t mid = (l + r) >> 1;
					if (clockwise(k, U[mid], U[mid + 1]) == 1) l = mid + 1; else ans = mid, r = mid;
				}
				point w2 = U[ans];
				return std::make_pair(w2, w1);
			}
			else {
				size_t l = 1, r = where2 + 1, ans = 0;
				while (l < r) {
					size_t mid = (l + r) >> 1;
					if (clockwise(k, D[mid], D[mid - 1]) == -1) ans = mid, l = mid + 1; else r = mid;
				}
				point w1 = D[ans];
				l = where2, r = D.size() - 1, ans = D.size() - 1;
				while (l < r) {
					size_t mid = (l + r) >> 1;
					if (clockwise(k, D[mid], D[mid + 1]) == -1) l = mid + 1; else ans = mid, r = mid;
				}
				point w2 = D[ans];
				return std::make_pair(w1, w2);
			}
		}
	}

	namespace comp3 {
		struct P3 {
			double x, y, z;

			P3 operator+(const P3& k1) const { return P3{ x + k1.x, y + k1.y, z + k1.z }; }

			P3 operator-(const P3& k1) const { return P3{ x - k1.x, y - k1.y, z - k1.z }; }

			P3 operator*(double k1) const { return P3{ x * k1, y * k1, z * k1 }; }

			P3 operator/(double k1) const { return P3{ x / k1, y / k1, z / k1 }; }

			double abs2() { return x * x + y * y + z * z; }

			double abs() { return sqrt(x * x + y * y + z * z); }

			P3 unit() { return (*this) / abs(); }

			int operator<(const P3 k1) const {
				if (cmp(x, k1.x) != 0) return x < k1.x;
				if (cmp(y, k1.y) != 0) return y < k1.y;
				return cmp(z, k1.z) == -1;
			}

			int operator==(const P3 k1) {
				return cmp(x, k1.x) == 0 && cmp(y, k1.y) == 0 && cmp(z, k1.z) == 0;
			}

			friend std::istream& operator>>(std::istream& io, P3& other) {
				io >> other.x >> other.y >> other.z;
				return io;
			}

			friend std::ostream& operator>>(std::ostream& io, const P3& other) {
				io << other.x << blank << other.y << blank << other.z;
				return io;
			}

			void scan() {
				double k1, k2, k3;
				scanf("%lf%lf%lf", &k1, &k2, &k3);
				x = k1;
				y = k2;
				z = k3;
			}
		};

		P3 cross(P3 k1, P3 k2) {
			return P3{ k1.y * k2.z - k1.z * k2.y, k1.z * k2.x - k1.x * k2.z, k1.x * k2.y - k1.y * k2.x };
		}

		double dot(P3 k1, P3 k2) { return k1.x * k2.x + k1.y * k2.y + k1.z * k2.z; }

		P3 turn3D(double k1, P3 l, P3 p) {
			l = l.unit();
			P3 ans;
			double c = cos(k1), s = sin(k1);
			ans.x = p.x * (l.x * l.x * (1 - c) + c) + p.y * (l.x * l.y * (1 - c) - l.z * s) +
				p.z * (l.x * l.z * (1 - c) + l.y * s);
			ans.y = p.x * (l.x * l.y * (1 - c) + l.z * s) + p.y * (l.y * l.y * (1 - c) + c) +
				p.z * (l.y * l.z * (1 - c) - l.x * s);
			ans.z = p.x * (l.x * l.z * (1 - c) - l.y * s) + p.y * (l.y * l.z * (1 - c) + l.x * s) +
				p.z * (l.x * l.x * (1 - c) + c);
			return ans;
		}

		using VP = std::vector<P3>;
		using VVP = std::vector<VP>;

		double Acos(double x) { return acos(std::max(-(double)1, std::min(x, (double)1))); }

		double Odist(P3 a, P3 b) {
			double r = Acos(dot(a, b));
			return r;
		}

		double r;
		P3 rnd;

		std::vector<double> solve(double a, double b, double c) {
			double r = sqrt(a * a + b * b), th = atan2(b, a);
			if (cmp(c, -r) == -1) return { 0 };
			else if (cmp(r, c) <= 0) return { 1 };
			else {
				double tr = pi - Acos(c / r);
				return { th + pi - tr, th + pi + tr };
			}
		}

		std::vector<double> jiao(P3 a, P3 b) {

			if (cmp(Odist(a, b), 2 * r) > 0) return { 0 };
			P3 rd = a * cos(r), z = a.unit(), y = cross(z, rnd).unit(), x = cross(y, z).unit();
			std::vector<double> ret = solve(-(dot(x, b) * sin(r)), -(dot(y, b) * sin(r)), -(cos(r) - dot(rd, b)));
			return ret;
		}

		double norm(double x, double l = 0, double r = 2 * pi) {
			while (cmp(x, l) == -1) x += (r - l);
			while (cmp(x, r) >= 0) x -= (r - l);
			return x;
		}

		double disLP(P3 k1, P3 k2, P3 q) {
			return (cross(k2 - k1, q - k1)).abs() / (k2 - k1).abs();
		}

		double disLL(P3 k1, P3 k2, P3 k3, P3 k4) {
			P3 dir = cross(k2 - k1, k4 - k3);
			if (sign(dir.abs()) == 0) return disLP(k1, k2, k3);
			return fabs(dot(dir.unit(), k1 - k2));
		}

		VP getFL(P3 p, P3 dir, P3 k1, P3 k2) {
			double a = dot(k2 - p, dir), b = dot(k1 - p, dir), d = a - b;
			if (sign(fabs(d)) == 0) return {};
			return { (k1 * a - k2 * b) / d };
		}

		VP getFF(P3 p1, P3 dir1, P3 p2, P3 dir2) {
			P3 e = cross(dir1, dir2), v = cross(dir1, e);
			double d = dot(dir2, v);
			if (sign(abs(d)) == 0) return {};
			P3 q = p1 + v * dot(dir2, p2 - p1) / d;
			return { q, q + e };
		}

		double getV(P3 k1, P3 k2, P3 k3, P3 k4) {
			return dot(cross(k2 - k1, k3 - k1), k4 - k1);
		}

		double rand_db() { return 1.0 * rand() / RAND_MAX; }

		VP convexHull2D(VP A, P3 dir) {
			P3 x = { (double)rand(), (double)rand(), (double)rand() };
			x = x.unit();
			x = cross(x, dir).unit();
			P3 y = cross(x, dir).unit();
			P3 vec = dir.unit() * dot(A[0], dir);
			std::vector<point> B;
			for (int i = 0; i < A.size(); i++) B.push_back(point{ dot(A[i], x), dot(A[i], y) });
			B = ConvexHull(B);
			A.clear();
			for (int i = 0; i < B.size(); i++) A.push_back(x * B[i].x + y * B[i].y + vec);
			return A;
		}

		namespace CH3 {
			VVP ret;
			std::set<std::pair<int, int> > e;
			size_t n;
			VP p, q;

			void wrap(int a, int b) {
				if (e.find({ a, b }) == e.end()) {
					int c = -1;
					for (int i = 0; i < n; i++)
						if (i != a && i != b) {
							if (c == -1 || sign(getV(q[c], q[a], q[b], q[i])) > 0) c = i;
						}
					if (c != -1) {
						ret.push_back({ p[a], p[b], p[c] });
						e.insert({ a, b });
						e.insert({ b, c });
						e.insert({ c, a });
						wrap(c, b);
						wrap(a, c);
					}
				}
			}

			VVP ConvexHull3D(VP _p) {
				p = q = _p;
				n = p.size();
				ret.clear();
				e.clear();
				for (auto& i : q) i = i + P3{rand_db() * 1e-4, rand_db() * 1e-4, rand_db() * 1e-4};
				for (int i = 1; i < n; i++) if (q[i].x < q[0].x) std::swap(p[0], p[i]), std::swap(q[0], q[i]);
				for (int i = 2; i < n; i++)
					if ((q[i].x - q[0].x) * (q[1].y - q[0].y) > (q[i].y - q[0].y) * (q[1].x - q[0].x))
						std::swap(q[1], q[i]), std::swap(p[1], p[i]);
				wrap(0, 1);
				return ret;
			}
		}

		VVP reduceCH(VVP A) {
			VVP ret;
			std::map<P3, VP> M;
			for (VP nowF : A) {
				P3 dir = cross(nowF[1] - nowF[0], nowF[2] - nowF[0]).unit();
				for (const P3& k1 : nowF) M[dir].push_back(k1);
			}
			for (std::pair<P3, VP> nowF : M) ret.push_back(convexHull2D(nowF.second, nowF.first));
			return ret;
		}

		std::pair<P3, P3> getF(VP F) {
			return std::make_pair(F[0], cross(F[1] - F[0], F[2] - F[0]).unit());
		}

		VVP ConvexCut3D(VVP A, P3 p, P3 dir) {
			VVP ret;
			VP sec;
			for (VP nowF : A) {
				size_t n = nowF.size();
				VP ans;
				int dif = 0;
				for (int i = 0; i < n; i++) {
					int d1 = sign(dot(dir, nowF[i] - p));
					int d2 = sign(dot(dir, nowF[(i + 1) % n] - p));
					if (d1 >= 0) ans.push_back(nowF[i]);
					if (d1 * d2 < 0) {
						P3 q = getFL(p, dir, nowF[i], nowF[(i + 1) % n])[0];
						ans.push_back(q);
						sec.push_back(q);
					}
					if (d1 == 0) sec.push_back(nowF[i]); else dif = 1;
					dif |= (sign(dot(dir, cross(nowF[(i + 1) % n] - nowF[i], nowF[(i + 1) % n] - nowF[i]))) == -1);
				}
				if (ans.size() > 0 && dif) ret.push_back(ans);
			}
			if (sec.size() > 0) ret.push_back(convexHull2D(sec, dir));
			return ret;
		}

		double vol(VVP A) {
			if (A.size() == 0) return 0;
			P3 p = A[0][0];
			double ans = 0;
			for (VP nowF : A)
				for (int i = 2; i < nowF.size(); i++)
					ans += abs(getV(p, nowF[0], nowF[i - 1], nowF[i]));
			return ans / 6;
		}

		VVP init(double INF = std::numeric_limits<double>::infinity()) {
			VVP pss(6, VP(4));
			pss[0][0] = pss[1][0] = pss[2][0] = { -INF, -INF, -INF };
			pss[0][3] = pss[1][1] = pss[5][2] = { -INF, -INF, INF };
			pss[0][1] = pss[2][3] = pss[4][2] = { -INF, INF, -INF };
			pss[0][2] = pss[5][3] = pss[4][1] = { -INF, INF, INF };
			pss[1][3] = pss[2][1] = pss[3][2] = { INF, -INF, -INF };
			pss[1][2] = pss[5][1] = pss[3][3] = { INF, -INF, INF };
			pss[2][2] = pss[4][3] = pss[3][1] = { INF, INF, -INF };
			pss[5][0] = pss[4][0] = pss[3][0] = { INF, INF, INF };
			return pss;
		}
	}
}