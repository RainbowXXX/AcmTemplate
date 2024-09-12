/*
矩阵类
矩阵乘法 矩阵快速幂
dt:dt[1 ~ SZ][1 ~ SZ]初始数据容器
Init0():O(SZ^2)置零矩阵
Init1():O(SZ^2)置单位矩阵
lh * rh:O(SZ^3)计算矩阵lh乘矩阵rh得到的矩阵
Pow(exp):O((SZ^3)*log(EXP))计算this ^ exp
*/
template <ll SZ, ll MOD>
struct Matrix
{
	ll dt[SZ + 1][SZ + 1];
	void Init0(void)
	{
		FOR(i, 0, SZ)
		FOR(j, 0, SZ)
		dt[i][j] = 0;
		return;
	}
	void Init1(void)
	{
		Init0();
		FOR(i, 0, SZ)
		dt[i][i] = 1;
		return;
	}
	friend Matrix operator*(const Matrix &lh, const Matrix &rh)
	{
		Matrix res;
		res.Init0();
		FOR(i, 1, SZ)
		FOR(j, 1, SZ)
		FOR(k, 1, SZ)
		res.dt[i][j] += lh.dt[i][k] * rh.dt[k][j] % MOD, res.dt[i][j] %= MOD;
		return res;
	}
	Matrix Pow(ll exp) const
	{
		assert(exp >= 0);
		Matrix res;
		res.Init1();
		Matrix base = *this;
		while (exp)
		{
			if (exp & 1)
				res = res * base;
			base = base * base;
			exp >>= 1;
		}
		return res;
	}
};
using mat = Matrix<2, MOD>;
/*
	cin:0 1 2 3 4 5 6
	cout:0 1 1 2 3 5 8
	输出第n位斐波那契数
*/
constexpr mat F =
	{0, 0, 0,
	 0, 1, 1,
	 0, 1, 0};
void Main(void)
{
	ll n;
	while (cin >> n)
		cout << F.Pow(n).dt[2][1] << EDL; // [1][2]也可
	return;
}