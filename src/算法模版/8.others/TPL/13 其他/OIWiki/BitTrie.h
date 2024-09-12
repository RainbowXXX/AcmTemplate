namespace trie
{
	const int MXN = 21;
	int ch[_ * (MXN + 1)][2], w[_ * (MXN + 1)], xorv[_ * (MXN + 1)];
	int tot = 0;

	int mknode()
	{
		++tot;
		ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
		return tot;
	}

	void maintain(int o)
	{
		w[o] = xorv[o] = 0;
		if (ch[o][0])
		{
			w[o] += w[ch[o][0]];
			xorv[o] ^= xorv[ch[o][0]] << 1;
		}
		if (ch[o][1])
		{
			w[o] += w[ch[o][1]];
			xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
		}
		w[o] = w[o] & 1;
	}

	void insert(int &o, int x, int dp)
	{
		if (!o)
			o = mknode();
		if (dp > MXN)
			return (void)(w[o]++);
		insert(ch[o][x & 1], x >> 1, dp + 1);
		maintain(o);
	}

	void erase(int o, int x, int dp)
	{
		if (dp > 20)
			return (void)(w[o]--);
		erase(ch[o][x & 1], x >> 1, dp + 1);
		maintain(o);
	}
} // namespace trie

// 所谓全局加一就是指，让这棵 trie 中所有的数值 +1。
// 形式化的讲，设 trie 中维护的数值有 v[1] ... v[n] , 全局加一后 其中维护的值应该变成 v[1]+1 ... v[n]+1
void addall(int o)
{
	swap(ch[o][0], ch[o][1]);
	if (ch[o][0])
		addall(ch[o][0]);
	maintain(o);
}

// 指的是将上述的两个 01-trie 进行合并，同时合并维护的信息。
int merge(int a, int b)
{
	if (!a)
		return b; // 如果 a 没有这个位置上的结点，返回 b
	if (!b)
		return a; // 如果 b 没有这个位置上的结点，返回 a
	/*
	  如果 `a`, `b` 都存在，
	  那就把 `b` 的信息合并到 `a` 上。
	*/
	w[a] = w[a] + w[b];
	xorv[a] ^= xorv[b];
	/* 不要使用 maintain()，
	  maintain() 是合并a的两个儿子的信息
	  而这里需要 a b 两个节点进行信息合并
	 */
	ch[a][0] = merge(ch[a][0], ch[b][0]);
	ch[a][1] = merge(ch[a][1], ch[b][1]);
	return a;
}