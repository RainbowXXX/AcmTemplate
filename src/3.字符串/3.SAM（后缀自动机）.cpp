template <typename T = char, size_t Sigma = 26, size_t Length = N>
class SAM {
	using Idx = int;
public:
	struct State {
		size_t len;
		Idx next[Sigma], link;
	};
protected:
	Idx tot, last;
	State states[Length << 1];
	constexpr void appand(const Idx& ch) {
		Idx cur = tot++, p = last;
		states[cur].len = states[last].len + 1;
		while (p != -1 && states[p].next[ch] == 0) {
			states[p].next[ch] = cur;
			p = states[p].link;
		}
		if (p == -1)
			states[cur].link = 0;
		else {
			Idx q = states[p].next[ch];
			if (states[p].len + 1 == states[q].len)
				states[cur].link = q;
			else {
				Idx clone = tot++;
				states[clone].len = states[p].len + 1;
				states[clone].link = states[q].link;
				memcpy(states[clone].next, states[q].next, Sigma * sizeof(Idx));
				while (p != -1 && states[p].next[ch] == q) {
					states[p].next[ch] = clone;
					p = states[p].link;
				}
				states[cur].link = clone; states[q].link = clone;
			}
		}
		last = cur;
	}
public:
	constexpr Idx ToIdx(T ch) { return ch - 'a'; }
	constexpr T FromIdx(Idx idx) { return idx + 'a'; }
	constexpr void init(const T* str, size_t len = -1) {
		State& begin = states[0];
		begin.len = 0; begin.link = -1;
		memset(begin.next, 0, Sigma * sizeof(Idx));
		tot = 1, last = 0;
		if (len == -1) for (int i = 0; str[i]; i++)
			appand(ToIdx(str[i]));
		else for (int i = 0; i < len; i++)
			appand(ToIdx(str[i]));
	}
};