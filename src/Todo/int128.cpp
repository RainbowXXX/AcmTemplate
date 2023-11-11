struct Int128 {
	int64_t high;
	uint64_t low;

	Int128(int64_t h, uint64_t l) : high(h), low(l) {}

	int operator <=> (const Int128& rhs) const{

	}

	// 加法
	Int128 operator+(const Int128& other) const {
		uint64_t sum_low = low + other.low;
		int64_t sum_high = high + other.high + (sum_low < low);
		return Int128(sum_high, sum_low);
	}

	// 减法
	Int128 operator-(const Int128& other) const {
		uint64_t diff_low = low - other.low;
		int64_t diff_high = high - other.high - (diff_low > low);
		return Int128(diff_high, diff_low);
	}

	// 乘法
	Int128 operator*(const Int128& other) const {
		int64_t a = static_cast<int64_t>(high);
		uint64_t b = low;
		int64_t c = static_cast<int64_t>(other.high);
		uint64_t d = other.low;

		int64_t ac = a * c;
		int64_t ad = a * d;
		int64_t bc = b * c;
		uint64_t bd = b * d;

		int64_t temp = ad + (bc & 0xFFFFFFFFULL) + (ac << 32);
		uint64_t result_low = bd + (temp & 0xFFFFFFFFULL);
		int64_t result_high = (ac >> 32) + (temp >> 32) + (bc >> 32);

		return Int128(result_high, result_low);
	}

	// 除法
	Int128 operator/(const Int128& other) const {
		if (other.high == 0 && other.low == 0) {
			// 除数为0，返回错误或抛出异常
			// 这里简化处理，返回0
			return Int128(0, 0);
		}

		// 如果被除数为0，则结果为0
		if (high == 0 && low == 0) {
			return Int128(0, 0);
		}

		Int128 quotient(0, 0); // 结果初始化为0
		Int128 remainder(*this); // 余数初始化为被除数

		// 如果除数小于或等于被除数，则继续执行除法操作
		while (remainder >= other) {
			Int128 temp = other;
			Int128 multiple(1, 0);

			// 使用位移来加快除法运算
			while (remainder >= (temp << 1)) {
				temp <<= 1;
				multiple <<= 1;
			}

			remainder = remainder - temp;
			quotient = quotient + multiple;
		}

		return quotient;
	}

	// 位运算
	Int128 operator&(const Int128& other) const {
		return Int128(high & other.high, low & other.low);
	}

	Int128 operator|(const Int128& other) const {
		return Int128(high | other.high, low | other.low);
	}

	Int128 operator^(const Int128& other) const {
		return Int128(high ^ other.high, low ^ other.low);
	}

	Int128 operator<<(int shift) const {
		if (shift >= 128 || shift <= -128) {
			return Int128(0, 0);
		}
		else if (shift >= 64) {
			return Int128(low << (shift - 64), 0);
		}
		else if (shift >= 0) {
			return Int128((high << shift) | (low >> (64 - shift)), low << shift);
		}
		else if (shift > -64) {
			return Int128(high >> (-shift) | (low << (64 + shift)), high << (64 + shift));
		}
		else {
			return Int128(high >> 63, high >> (shift + 127));
		}
	}

	void operator<<=(int shift) {
		if (shift >= 128 || shift <= -128) {
			high = low = 0;
		}
		else if (shift >= 64) {
			high = low << (shift - 64); low = 0;
		}
		else if (shift >= 0) {
			high = (high << shift) | (low >> (64 - shift));
			low = low << shift;
		}
		//else if (shift > -64) {
		//	return Int128(high >> (-shift) | (low << (64 + shift)), high << (64 + shift));
		//}
		//else {
		//	return Int128(high >> 63, high >> (shift + 127));
		//}
	}

	operator bool() {
		return high or low;
	}
};

using int128 = Int128;