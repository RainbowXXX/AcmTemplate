int ManacherRead(char* str)
{
	char ch; int i;
	str[0] = '$'; str[0 + 1] = '#';
	for (i = 2; (ch = getchar()) != '\n'; i++) { if (ch == EOF) if (i == 2) return EOF; else break; str[i] = ch; i++; str[i] = '#'; }
	str[i] = '^'; str[i + 1] = '\0';
	return i;
}