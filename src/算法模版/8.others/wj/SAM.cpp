//有时会与序列自动机结合，序列自动机很简单不用板子
struct SAM
{
    int tot, last;
    struct node
    {
        int fa, len, son[26];
    } tr[N << 1];

    void add_node(int len)
    {
        tr[++tot].len = len;
        tr[tot].fa = -1;
        memset(tr[tot].son, 0, sizeof tr[tot].son);
    }

    SAM()
    {
        tot = -1, last = 0;
        add_node(0);
    }
    
    void clear()
    {
        tot = -1, last = 0;
        add_node(0);
    }

    void insert(int c)
    {
        add_node(tr[last].len + 1);
        int p = last, cur = tot;
        while (p != -1 and !tr[p].son[c])
        {
            tr[p].son[c] = cur;
            p = tr[p].fa;
        }
        if (p == -1)
            tr[cur].fa = 0;
        else
        {
            int q = tr[p].son[c];
            if (tr[q].len == tr[p].len + 1)
                tr[cur].fa = q;
            else
            {
                add_node(tr[p].len + 1);
                int nq = tot;
                memcpy(tr[nq].son, tr[q].son, sizeof tr[q].son);
                tr[nq].fa = tr[q].fa;
                tr[cur].fa = tr[q].fa = nq;
                while (p >= 0 and tr[p].son[c] == q)
                {
                    tr[p].son[c] = nq, p = tr[p].fa;
                }
            }
        }
        last = cur;
    }
}sam;
