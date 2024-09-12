// for (ll i = v_hd[now]; i != NUL; i = e_nxt[i])
template <ll V_SZ, ll E_SZ>
struct Graph
{
	static constexpr ll NUL = -1;
	ll v_sz, e_sz;
	ll v_hd[V_SZ];
	ll e_ed[E_SZ];
	ll e_wt[E_SZ];
	ll e_nxt[E_SZ];
	void Init(ll v_sz)
	{
		this->v_sz = v_sz;
		e_sz = 0;
		FOR(i, 0, v_sz)
		v_hd[i] = NUL;
		return;
	}
	void Push(ll bg, ll ed, ll wt)
	{
		++e_sz;
		e_ed[e_sz] = ed;
		e_wt[e_sz] = wt;
		e_nxt[e_sz] = v_hd[bg];
		v_hd[bg] = e_sz;
		return;
	}
};
Graph<SZ, SZ> G;