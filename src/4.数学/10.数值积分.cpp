namespace integration {
	double Fun2(double x, double y) {
		return std::sqrt(x * x + y * y);//二重积分函数
	}
	double simpsonX2(double a, double b, double y) {//a,d为积分下、上限，y为被固定的y值
		double c = (b + a) / 2.0;
		return (Fun2(a, y) + 4 * Fun2(c, y) + Fun2(b, y)) * (b - a) / 6.0;//对x的辛普森近似
	}

	double adspX2(double a, double b, double y, double eps, double S) {//对x的自适应辛普森递归
		double c = (b + a) / 2.0;
		double L = simpsonX2(a, c, y), R = simpsonX2(c, b, y);
		if (abs(L + R - S) <= 15.0 * eps) {
			return L + R + (L + R - S) / 15.0;
		}
		return adspX2(a, c, y, eps / 2.0, L) + adspX2(c, b, y, eps / 2.0, R);
	}
	double inte2(double a, double b, double y, double eps) {//固定y后，对x的积分
		return adspX2(a, b, y, eps, simpsonX2(a, b, y));
	}
	double simpsonY2(double xa, double xb, double ya, double yb, double eps) {
		double yc = (ya + yb) / 2.0;
		return (inte2(xa, xb, ya, eps) + 4 * inte2(xa, xb, yc, eps) + inte2(xa, xb, yb, eps)) * (yb - ya) / 6.0;//对y的辛普森近似
	}
	double adspY2(double xa, double xb, double ya, double yb, double eps, double S) {//对y的自适应辛普森递归
		double L = simpsonY2(xa, xb, ya, (ya + yb) / 2, eps);
		double R = simpsonY2(xa, xb, (ya + yb) / 2, yb, eps);
		if (abs(L + R - S) <= 15.0 * eps) {
			return L + R + (L + R - S) / 15.0;
		}
		return adspY2(xa, xb, ya, (ya + yb) / 2.0, eps / 2.0, L) + adspY2(xa, xb, (ya + yb) / 2.0, yb, eps / 2.0, R);
	}
	double intergation2(double xa, double xb, double ya, double yb, double eps) {//求二重积分
		return adspY2(xa, xb, ya, yb, eps, simpsonY2(xa, xb, ya, yb, eps));
	}
}