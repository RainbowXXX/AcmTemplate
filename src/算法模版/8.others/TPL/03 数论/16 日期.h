//似乎有问题
struct Date
{
	static constexpr ll md[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
									 {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

	ll year, month, day;

	bool YearKind(void) { return ((year % 4 == 0 and year % 100 != 0) or year % 400 == 0); }
	bool Check(ll l, ll r) { return (l <= year and year <= r and 1 <= month and month <= 12 and 1 <= day and day <= md[YearKind()][month]); }
	ll WeekKind(void) { return (day + 1 + 2 * (month + (month < 3) * 12) + 3 * (month + (month < 3) * 12 + 1) / 5 + year - (month < 3) + (year - (month < 3)) / 4 - (year - (month < 3)) / 100 + (year - (month < 3)) / 400) % 7; }
	ll Dist(Date rhs)
	{
		ll res = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + year / 400 + day - ((rhs.year - 1) * 365 + (rhs.year - 1) / 4 - (rhs.year - 1) / 100 + (rhs.year - 1) / 400 + rhs.day);
		FOR(i, 1, month)
		res += md[YearKind()][i];
		FOR(i, 1, rhs.month)
		res -= md[rhs.YearKind()][i];
		return res;
	}
};
Date date;