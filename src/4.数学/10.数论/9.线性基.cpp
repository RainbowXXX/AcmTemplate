namespace Hamel {
	template<typename _Ty>
	class HamelXor {
	public:
		static const size_t SpaceSize = sizeof(_Ty) << 3LL;
	protected:
		_Ty space[SpaceSize];
		constexpr void intersect(_Ty x) {
			for (int i = SpaceSize - 1; i >= 0; --i) {
				if (x >> i & 1) {
					if (space[i]) x ^= space[i];
					else { space[i] = x; break; }
				}
			}
		}
	public:
		HamelXor() { std::fill(space, space + SpaceSize, 0); }
		constexpr void insert(_Ty x) {
			for (int i = SpaceSize - 1; i >= 0; --i) {
				if (!(x >> i)) continue;
				if (!space[i]) { space[i] = x; break; }
				x ^= space[i];
			}
		}
		constexpr bool contains(_Ty x) const {
			for (int i = SpaceSize - 1; i >= 0; --i) {
				if (!(x >> i)) continue;
				if (!space[i]) return false;
				x ^= space[i];
			}
			return true;
		}
		constexpr void merge(const HamelXor& other) {
			for (int i = SpaceSize - 1; i >= 0; --i)
				if (other.space[i]) insert(other.space[i]);
		}
		constexpr void intersect(const HamelXor& other) {
			for (int i = SpaceSize - 1; i >= 0; --i)
				if (other.space[i] && space[i]) intersect(other.space[i]);
		}
	};
}