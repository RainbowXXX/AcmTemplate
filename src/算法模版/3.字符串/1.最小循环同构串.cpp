template<typename _Ty>
int minString(_Ty* str, int len) {
	int i = 0, j = 1, k = 0, ir = 0, jr = 0;
	while (i < len && j < len && k < len) {
		ir = i + k - len; ir += (ir >> 31) & len;
		jr = j + k - len; jr += (jr >> 31) & len;
		if (str[ir] == str[jr]) k++;
		else {
			if (str[ir] > str[jr]) i += k + 1;
			else j += k + 1;
			i += (i == j);
			k = 0;
		}
	}

	k = std::min(i, j);

	return k;
}