const int IOBufferSize = 1e7 + 7;
class Mfout {
public:
	const static int IOBufferSize = (int)1e7 + 7;
	Mfout() { buffer[0] = 0; out_tail = buffer; bufferend = buffer + IOBufferSize; rmost = bufferend - 20; }
	~Mfout() { if (out_tail != buffer) fwrite(buffer, out_tail - buffer, 1, stdout); }
	inline int flush() { if (out_tail != buffer) fwrite(buffer, out_tail - buffer, 1, stdout), out_tail = buffer; return 0; }
	inline Mfout& operator << (long x) { return outnum(x); }
	inline Mfout& operator << (int x) { return outnum(x); }
	inline Mfout& operator << (long long x) { return outnum(x); }
	inline Mfout& operator << (const std::string_view& str) {
		if (out_tail + str.length() > rmost) flush(), fwrite(str.data(), str.length(), 1, stdout);
		else memcpy(out_tail, str.data(), str.length()), out_tail += str.length();
		return *this;
	}
	inline Mfout& operator << (char x) {
		(void)(out_tail == rmost && flush());
		*out_tail++ = x; return *this;
	}

private:
	constexpr Mfout& outnum(long long x) {
		if (!x) *out_tail++ = '0';
		else {
			if (x < 0) *out_tail++ = '-', x = -x;
			long long t = x;
			char* s_tail = out_tail;
			while (t != 0) s_tail++, t /= 10; out_tail = s_tail;
			while (x) *--s_tail = x % 10 + '0', x /= 10;
		}
		if (out_tail > rmost) fwrite(buffer, out_tail - buffer, 1, stdout), out_tail = buffer;
		return *this;
	}

	char buffer[IOBufferSize];
	char* out_tail, * bufferend, * rmost;
};
static Mfout fout;