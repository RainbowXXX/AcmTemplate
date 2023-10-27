struct PAM {
    struct node{
        int len, fail, son[26], siz;
        void init(int _len)
        {
            memset(son, 0, sizeof son);
            fail = siz = 0;
            len  = _len;
        }
    }tr[N];
    
    ll num, last[2], ans, L, R, str[N];
    
    void clear()
    {
        last[0] = last[1] = 0;
        ans = 0, num = 1;
        L = 1e5 + 8, R = 1e5 + 7;
        tr[0].init(0);
        memset(str, -1, sizeof str);
        tr[1].init(-1);
        tr[0].fail = 1;
    }
    
    int getFail(int p, int d)
    {
        if(d)
            while(str[R - tr[p].len - 1] != str[R])
                p = tr[p].fail;
        else
            while(str[L + tr[p].len + 1] != str[L])
                p = tr[p].fail;
        return p;
    }
    
    void insert(int x, int d)
    {
        (d != 0) ? str[++R] = x : str[--L] = x;
        int fa = getFail(last[d], d);
        int now = tr[fa].son[x];
        if(not now)
        {
            now = ++num;
            tr[now].init(tr[fa].len + 2);
            tr[now].fail = tr[getFail(tr[fa].fail, d)].son[x];
            tr[now].siz = tr[tr[now].fail].siz + 1;
            tr[fa].son[x] = now;
        }
        last[d] = now;
        if(R - L + 1 == tr[now].len) last[d^1] = now;
        ans += tr[now].siz;
    }
}pa;
