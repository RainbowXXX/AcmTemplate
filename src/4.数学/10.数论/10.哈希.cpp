constexpr int r = 47;
constexpr int mask = 0xfffffff8;
constexpr std::uint64_t seed = 0;
constexpr std::uint64_t m = 0xc6a4a7935bd1e995ull;
template<typename T>
struct myhash {
	std::uint64_t operator()(const T& _Keyval) const {
		std::uint_fast64_t k = 0;
		std::size_t len = sizeof(T);
		std::uint_fast64_t ret = seed ^ (len * m);
		std::uint_fast8_t* begin = (std::uint_fast8_t*)&_Keyval, * end = (begin + (len & mask));
		for (; begin != end; begin += 8) k = (*(std::uint_fast64_t*)begin) * m, k ^= k >> r, k *= m, ret ^= k, ret *= m;
		switch (len & 7) {
		case 7: ret ^= ((std::uint_fast64_t)end[6]) << 48;
		case 6: ret ^= ((std::uint_fast64_t)end[5]) << 40;
		case 5: ret ^= ((std::uint_fast64_t)end[4]) << 32;
		case 4: ret ^= ((std::uint_fast64_t)end[3]) << 24;
		case 3: ret ^= ((std::uint_fast64_t)end[2]) << 16;
		case 2: ret ^= ((std::uint_fast64_t)end[1]) << 8;
		case 1: ret ^= ((std::uint_fast64_t)end[0]), ret *= m;
		};
		ret ^= ret >> r, ret *= m, ret ^= ret >> r;
		return ret;
	}
};
template<>
struct myhash<std::string> {
	std::uint64_t operator()(const std::string& _Keyval) const {
		std::uint_fast64_t k = 0;
		std::size_t len = _Keyval.size();
		std::uint_fast64_t ret = seed ^ (len * m);
		std::uint_fast8_t* begin = (std::uint_fast8_t*)_Keyval.c_str(), * end = (begin + (len & mask));
		for (; begin != end; begin += 8) k = (*(std::uint_fast64_t*)begin) * m, k ^= k >> r, k *= m, ret ^= k, ret *= m;
		switch (len & 7) {
		case 7: ret ^= ((std::uint_fast64_t)end[6]) << 48;
		case 6: ret ^= ((std::uint_fast64_t)end[5]) << 40;
		case 5: ret ^= ((std::uint_fast64_t)end[4]) << 32;
		case 4: ret ^= ((std::uint_fast64_t)end[3]) << 24;
		case 3: ret ^= ((std::uint_fast64_t)end[2]) << 16;
		case 2: ret ^= ((std::uint_fast64_t)end[1]) << 8;
		case 1: ret ^= ((std::uint_fast64_t)end[0]), ret *= m;
		};
		ret ^= ret >> r, ret *= m, ret ^= ret >> r;
		return ret;
	}
};
template <class A, class B>
class hash_map : public std::unordered_map<A, B, myhash<A>> {  };