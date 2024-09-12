struct Date
{
	ll year, month, day;
	Date() : year(), month(), day() {}
	Date(ll year, ll month, ll day) : year(year), month(month), day(day) {}
	bool isCurLeapYear() { return isLeapYear(year); }
	int getCurMonthDays() { return getMonthDays(month, year); }
	ll getDayStamp() const
	{
		ll ret = 0;
		ret +=
			(year - 1) * 365 +
			(year - 1) / 4 -
			(year - 1) / 100 +
			(year - 1) / 400;
		for (int i = 1; i < month; ++i)
			ret += getMonthDays(i, year);
		ret += day - 1;
		return ret;
	}
	ll getDist(const Date &rhs) const { return getDayStamp() - rhs.getDayStamp(); }
	static bool isLeapYear(int year)
	{
		if (year < 0)
			year = -year - 1;
		return (year % 4 == 0 and year % 100 != 0) or year % 400 == 0;
	}
	static int getMonthDays(int month, int year)
	{
		int days;
		switch (month)
		{
		case 2:
			days = isLeapYear(year) ? 29 : 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;
		default:
			days = 31;
			break;
		}
		return days;
	}
};