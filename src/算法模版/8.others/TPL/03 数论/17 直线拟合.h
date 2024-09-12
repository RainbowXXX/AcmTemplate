/*
直线拟合
已知a[] 构造等差数列c[]
让(a[i]-c[i])^2,i从1到n代入的和最小
*/
db xs = 0.0, ys = 0.0, xxs = 0.0, xys = 0.0;
FOR(i, 1, n)
{
	xs += i;
	ys += a[i];
	xxs += i * i;
	xys += i * a[i];
}
db k = (db)(n * xys - xs * ys) / (n * xxs - xs * xs);
db b = (db)(xxs * ys - xs * xys) / (n * xxs - xs * xs);
FOR(i, 1, n)
c[i] = k * i + b;