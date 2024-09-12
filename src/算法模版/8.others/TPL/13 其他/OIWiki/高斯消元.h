const int maxn = 505;
const double eps = 1e-8;
double A[maxn << 1][maxn], x[maxn]; // A矩阵中每一行1~n存系数，n+1为答案，m个方程m行，x是最终的答案
// 注意空间要多开几个，还要考虑n，m不同的情况
int n, m;
int Guass(int n, int m) // 有n个未知数，m个方程
{
	int i = 1, j = 1, k, r, c;
	while (i <= m && j <= n) // 正在处理第i个方程，解第j个未知数
	{
		r = i; // 找到绝对值最大的系数，防止除数为0的情况，使得其他方程组系数不会变得太大
		for (k = i + 1; k <= m; k++)
			if (fabs(A[k][j]) > fabs(A[r][j]))
				r = k;
		if (fabs(A[r][j]) >= eps) // 出现为0的情况，说明此项已经被消掉了，直接用进行下一个未知数，而方程不变,不过这个时候，一般来说跳过的这个元素就没有固定解啦
		{
			for (c = 1; c <= n + 1; c++)
				swap(A[i][c], A[r][c]); // 交换
			for (k = i + 1; k <= m; k++)
				if (fabs(A[k][j]) >= eps)
				{
					double f = A[k][j] / A[i][j];
					for (c = j; c <= n + 1; c++) // 当前方程j前面的系数都是0
						A[k][c] -= f * A[i][c];
				}
			i++; // 获取下一个方程
		}
		j++; // 去消下一个未知数
	}
	// 必须先判无解再判断多解
	for (k = i; k <= m; k++)
		if (fabs(A[k][n + 1]) >= eps)
			return 0; // 若有一行系数为0但是不为答案，则无解
	if (i <= n)
		return 2; // 如果被你处理出来的方程没有n个，就会出现多解。(i=n表示解决了n-1个方程)
	for (int i = n; i >= 1; i--)
	{
		for (j = i + 1; j <= n; j++)
			A[i][n + 1] -= A[i][j] * x[j];
		x[i] = A[i][n + 1] / A[i][i];
	}
	// 最终统计出来的答案x[i]肯定是对应的第i个元素的解哦,换的只是方程的顺序
	return 1; // 拥有唯一解
}