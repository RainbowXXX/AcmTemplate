/*
树状数组07
二维区间修改 二维区间查询
row_sz,col_sz:当前大小
Init(row_sz,col_sz):O(N)初始化
Mdf(lu_row,lu_col,rd_row,rd_col,d):O(logNlogN)使a[lu_row ~ rd_row][lu_col ~ rd_col]+=d
Qry(lu_row,lu_col,rd_row,rd_col):O(logNlogN)查询Sum( (lu_row,lu_col) ~ (rd_row,rd_col) )
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
		FOR(k, 0, 3)
		FOR(i, 0, row_sz)
		FOR(j, 0, col_sz)
		dt[k][i][j] = 0;
		return;
	}
	void Mdf(ll lu_row, ll lu_col, ll rd_row, ll rd_col, ll d)
	{
		MdfA(lu_row, lu_col, d);
		MdfA(lu_row, rd_col + 1, -d);
		MdfA(rd_row + 1, lu_col, -d);
		MdfA(rd_row + 1, rd_col + 1, d);
		return;
	}
	ll Qry(ll lu_row, ll lu_col, ll rd_row, ll rd_col) { return QryS(rd_row, rd_col) - QryS(rd_row, lu_col - 1) - QryS(lu_row - 1, rd_col) + QryS(lu_row - 1, lu_col - 1); }

protected:
	ll dt[4][ROW_SZ + 1][COL_SZ + 1];
	ll Lowbit(ll x) { return x & (-x); }
	void MdfD(ll k, ll row, ll col, ll d)
	{
		for (ll i = row; i <= row_sz; i += Lowbit(i))
			for (ll j = col; j <= col_sz; j += Lowbit(j))
				dt[k][i][j] += d;
		return;
	}
	void MdfA(ll row, ll col, ll d)
	{
		MdfD(0, row, col, d);
		MdfD(1, row, col, d * row);
		MdfD(2, row, col, d * col);
		MdfD(3, row, col, d * row * col);
		return;
	}
	ll QryS(ll row, ll col)
	{
		ll res = 0;
		for (ll i = row; i > 0; i -= Lowbit(i))
			for (ll j = col; j > 0; j -= Lowbit(j))
			{
				res += (row + 1) * (col + 1) * dt[0][i][j];
				res -= (col + 1) * dt[1][i][j];
				res -= (row + 1) * dt[2][i][j];
				res += dt[3][i][j];
			}
		return res;
	}
};
BIT<SZ, SZ> bit;