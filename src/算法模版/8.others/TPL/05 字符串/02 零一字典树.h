template <ll EXP>
struct Trie
{
	struct Node
	{
		ll cnt;
		Node *son[2];

		Node()
		{
			cnt = 0;
			son[0] = son[1] = nullptr;
		}
	};
	Node *rt;

	Trie() { rt = new Node(); }

	void Insert(ll x)
	{
		Node *now = rt;
		ROF(i, EXP, 0)
		{
			ll b = (x >> i) & 1;
			if (now->son[b] == nullptr)
				now->son[b] = new Node();
			now = now->son[b];
			++(now->cnt);
		}
		return;
	}
	void Erase(ll x)
	{
		Node *now = rt;
		ROF(i, EXP, 0)
		{
			ll b = (x >> i) & 1;
			now = now->son[b];
			--(now->cnt);
		}
		return;
	}
	ll Qry(ll x, ll h, Node *now, ll dep)
	{
		ll res = 0;
		Node *tmp;
		ll x_b = (x >> dep) & 1;
		ll h_b = (h >> dep) & 1;

		if (h_b == 1)
		{
			tmp = now->son[1 - x_b];
			if (tmp != nullptr)
				res += Qry(x, h, tmp, dep - 1);
		}
		else
		{
			tmp = now->son[1 - x_b];
			if (tmp != nullptr)
				res += tmp->cnt;
			tmp = now->son[x_b];
			if (tmp != nullptr)
				res += Qry(x, h, tmp, dep - 1);
		}

		return res;
	}
};
Trie<31> trie;