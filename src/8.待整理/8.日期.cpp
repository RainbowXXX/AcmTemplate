bool isLeapYear(int year) {
	return (year % 4 == 0 and year % 100 != 0) or year % 400 == 0;
}

int getMonth(int month, int year)
{
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