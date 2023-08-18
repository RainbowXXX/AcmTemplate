template <typename T = int, size_t Sigma = 2, size_t Length = N>
struct Trie{
	using Idx = int;
protected:
	Idx root;
	size_t tot;
	struct Node {
		T endpos;
		Idx next[Sigma];
	}states[Length << 2];
	Idx add() {
		states[tot].endpos = -1;
		std::fill(states[tot].next, states[tot].next + Sigma, 0);
		return tot++;
	}
public:
	Trie() : tot(0), root(add()) {}
	void clear() {
		tot = 0;
		root = add();
	}
};