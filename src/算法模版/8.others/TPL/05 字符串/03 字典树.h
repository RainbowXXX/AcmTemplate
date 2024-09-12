template <ll SZ>
struct Trie
{
public:
	static constexpr ll NUL = 0;

	ll sz;

	void Init(void) { sz = 0; }
	void Clear(void)
	{
		FOR(j, 0, 25)
		FOR(i, 0, sz)
		nxt[j][i] = NUL;
		FOR(i, 0, sz)
		ext[i] = false;
		return;
	}
	// from 1
	void Insert(char s[], ll len)
	{
		ll p = 0;
		FOR(i, 1, len)
		{
			ll c = s[i] - 'a';
			if (nxt[c][p] == NUL)
				nxt[c][p] = ++sz;
			p = nxt[c][p];
		}
		ext[p] = true;
		return;
	}
	bool Find(char s[], ll len)
	{
		ll p = 0;
		FOR(i, 1, len)
		{
			ll c = s[i] - 'a';
			if (nxt[c][p] == NUL)
				return false;
			p = nxt[c][p];
		}
		return ext[p];
	}

protected:
	ll nxt[26 + 1][SZ];
	// 该节点结尾的字符串是否存在(或其他信息)
	bool ext[SZ];
};
Trie<SZ> trie;