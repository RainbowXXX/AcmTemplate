/*
树状数组06
二维区间修改 单点查询
row_sz,col_sz:当前大小
Init(row_sz,col_sz):O(N)初始化
Mdf(lu_row,lu_col,rd_row,rd_col,d):O(logNlogN)使a[lu_row ~ rd_row][lu_col ~ rd_col]+=d
Qry(row,col):O(logNlogN)查询a[row][col]
d[i][j]=a[i][j] - (a[i-1][j]+a[i][j-1]-a[i-1][j-1])
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
	void Mdf(ll lu_row, ll lu_col, ll rd_row, ll rd_col, ll d)
	{
		MdfD(lu_row, lu_col, d);
		MdfD(lu_row, rd_col + 1, -d);
		MdfD(rd_row + 1, lu_col, -d);
		MdfD(rd_row + 1, rd_col + 1, d);
		return;
	}
	ll Qry(ll row, ll col)
	{
		ll res = 0;
		for (ll i = row; i > 0; i -= Lowbit(i))
			for (ll j = col; j > 0; j - Lowbit(j))
				res += dt[i][j];
		return res;
	}

protected:
	ll dt[ROW_SZ + 1][COL_SZ + 1];
	ll Lowbit(ll x) { return x & (-x); }
	void MdfD(ll row, ll col, ll d)
	{
		for (ll i = row; i <= row_sz; i += Lowbit(i))
			for (ll j = col; j <= col_sz; j += Lowbit(j))
				dt[i][j] += d;
		return;
	}
};
BIT<SZ, SZ> bt;