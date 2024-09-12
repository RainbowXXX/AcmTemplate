using i128 = __int128;
std::istream &operator>>(std::istream &is, i128 &aim)
{
	STR tmp;
	is >> tmp;
	bool sign = false;
	aim = 0;
	for (const auto &c : tmp)
		if (c == '-')
			sign = true;
		else
			aim = aim * 10 + c - '0';
	if (sign)
		aim = -aim;
	return is;
}
std::ostream &operator<<(std::ostream &os, const i128 &aim)
{
	i128 tmp = aim;
	if (tmp == 0)
		os << 0;
	else
	{
		if (tmp < 0)
		{
			os << '-';
			tmp = -tmp;
		}
		STR res;
		while (tmp)
		{
			res.push_back('0' + (tmp % 10));
			tmp /= 10;
		}
		std::reverse(res.begin(), res.end());
		os << res;
	}
	return os;
}