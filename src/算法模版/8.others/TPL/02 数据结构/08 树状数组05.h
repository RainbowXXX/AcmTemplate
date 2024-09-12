/*
树状数组05
单点修改 二维前缀查询
row_sz,col_sz:当前大小
Init(row_sz,col_sz):O(N)初始化
Mdf(row,col,d):O(logNlogN)使a[row][col]+=d;
Qry(row,col):O(logNlogN)查询Sum( (1,1) ~ (row,col) )
*/
template <ll ROW_SZ, ll COL_SZ>
struct BIT
{
public:
	ll row_sz, col_sz;
	void Init(ll row_sz, ll col_sz)
	{
		this->row_sz = row_sz;
		this->col_sz = col_sz;
		FOR(i, 0, row_sz)
		FOR(j, 0, col_sz)
		dt[i][j] = 0;
		return;
	}
	void Mdf(ll row, ll col, ll d)
	{
		for (ll i = row; i <= row_sz; i += Lowbit(i))
			for (ll j = col; j <= col_sz; j += Lowbit(j))
				dt[i][j] += d;
		return;
	}
	ll Qry(ll row, ll col)
	{
		ll res = 0;
		for (ll i = row; i > 0; i -= Lowbit(i))
			for (ll j = col; j > 0; j -= Lowbit(j))
				res += dt[i][j];
		return res;
	}

protected:
	ll dt[ROW_SZ + 1][COL_SZ + 1];
	ll Lowbit(ll x) { return x & (-x); }
};
BIT<SZ, SZ> bt;