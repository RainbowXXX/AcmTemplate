struct Date {
	ll year, month, day;
	Date() : year(1), month(1), day(1) {}
	Date(ll year, ll month, ll day) : year(year), month(month), day(day) {}
	void set(ll _year, ll _month, ll _day) {
		year = _year;
		month = _month;
		day = _day;
	}
	bool isCurLeapYear() {
		return isLeapYear(year);
	}
	int getCurMonthDays() {
		return getMonthDays(month, year);
	}
	ll getDayStamp() const {
		ll ret = 0, cyear = year;
		if (cyear < 0) cyear = -year;
		ret +=
			(cyear - 1) * 365 +
			(cyear - 1) / 4 -
			(cyear - 1) / 100 +
			(cyear - 1) / 400;
		if (year < 0) cyear--;
		for (int i = 1; i < month; i++) ret += getMonthDays(i, cyear);
		ret += day;
		if (year < 0) ret = -(ret - 1);
		return ret;
	}
	ll distance(const Date& rhs) const {
		return getDayStamp() - rhs.getDayStamp();
	}
	ll weekKind() {
		return (getDayStamp() % 7 + 7) % 7;
		//return (day + 1 + 2 * (month + (month < 3) * 12) + 3 * (month + (month < 3) * 12 + 1) / 5 + year - (month < 3) + (year - (month < 3)) / 4 - (year - (month < 3)) / 100 + (year - (month < 3)) / 400) % 7;
	}
	static bool isLeapYear(int year) {
		if (year < 0) year = -year - 1;
		return (year % 4 == 0 and year % 100 != 0) or year % 400 == 0;
	}
	static int getMonthDays(int month, int year) {
		int days;
		switch (month) {
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
	static bool isValid(int year, int month, int day) {
		if (year == 0) return false;
		if (month <= 0 or month > 12) return false;
		if (day <= 0 or day > getMonthDays(month, year)) return false;
		return true;
	}
};