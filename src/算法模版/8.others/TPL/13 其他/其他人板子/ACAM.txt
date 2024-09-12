struct ACM {
    int root, tot, siz;
    struct node{
        int son[30], fa, cnt;
    }tr[N]{};

    ACM() {
        tot = 0, siz = 26;
        root = add();
    }

    int add() {
        memset(tr[tot].son, -1, sizeof tr[tot].son);
        tr[tot].cnt = 0;
        return tot++;
    }

    //多组样例需要清空，单组因为有构造器可以不清空
    void clear() {
        tot = 0, siz = 26;
        root = add();
    }

    //根据题目要求可能需要两个参数
    void insert(const string &s, int v) {
        int p = root;
        for (char i: s) {
            int x = i - 'a';
            if (tr[p].son[x] == -1) {
                tr[p].son[x] = add();
            }
            p = tr[p].son[x];
        }
        tr[p].cnt ++;
    }

    int find(const string &s) {//这里是统计s出现了几次，但一般情况下，find用不到
        int now = root, ans = 0;
        for (char i: s) {
            int x = i - 'a';
            now = tr[now].son[x];
            for (int j = now; j != -1 and tr[j].cnt != -1; j = tr[j].fa) {
                ans += tr[j].cnt, tr[j].cnt = -1;
            }
        }
        return ans;
    }

    //核心部分
    void build() {
        queue<int> q;
        for (int i = 0; i < siz; i++) {
            if (~tr[root].son[i]) {
                tr[tr[root].son[i]].fa = root;
                q.push(tr[root].son[i]);
            } else
                tr[root].son[i] = root;
        }
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (int i = 0; i < siz; i++) {
                if (~tr[p].son[i]) {
                    tr[tr[p].son[i]].fa = tr[tr[p].fa].son[i];
                    /*这里反向构建fail树
                    in[tr[tr[p].fa].son[i]]++
                    ...
                    ...
                    */ 
                    q.push(tr[p].son[i]);
                } else {
                    tr[p].son[i] = tr[tr[p].fa].son[i];
                }
            }
        }
    }
} ac;