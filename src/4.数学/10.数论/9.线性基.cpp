namespace Hamel {
    // 异或线性基
	template<typename _Ty = int, typename std::enable_if_t<std::is_integral_v<_Ty>, int> = 0>
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
		void clear() { std::fill(space, space + SpaceSize, 0); }
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
		constexpr void intersect(const HamelXor<_Ty>& other) {
			_Ty space1[SpaceSize], space2[SpaceSize], ans[SpaceSize]{};
			for (int i = 0; i < SpaceSize; i++) {
				space1[i] = space2[i] = other.space[i];
				int j = i;
				_Ty x = space[i], T = 0;
				if (!x) continue;
				for (; j >= 0; j--) {
					if ((x >> j) & 1) {
						if (not space1[j]) break;
						x ^= space1[j], T ^= space2[j];
					}
				}
				if (!x) ans[i] = T;
				else space1[j] = x, space2[j] = T; 
			}
			for (int i = 0; i < SpaceSize; i++) space[i] = ans[i];
		}
		// 比较慢,不建议用
		constexpr void __intersect(const HamelXor<_Ty>& other) {
			for (int i = SpaceSize - 1; i >= 0; --i)
				if (other.space[i] && space[i]) intersect(other.space[i]);
		}
		constexpr HamelXor<_Ty> intersection(const HamelXor<_Ty>& other) {
			HamelXor<_Ty> ans;
			_Ty space1[SpaceSize], space2[SpaceSize];
			for (int i = 0; i < SpaceSize; i++) {
				space1[i] = space2[i] = other.space[i];
				int j = i;
				_Ty x = space[i], T = 0;
				if (!x) continue;
				for (; j >= 0; j--) {
					if ((x >> j) & 1) {
						if (not space1[j]) break;
						x ^= space1[j], T ^= space2[j];
					}
				}
				if (!x) ans.space[i] = T;
				else space1[j] = x, space2[j] = T;
			}
			for (int i = 0; i < SpaceSize; i++) space[i] = ans.space[i];
			return ans;
		}
	};
}