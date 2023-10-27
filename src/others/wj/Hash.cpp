/* 
9223372036854775837 = (1ull << 63) + 29
16140901064495857669 = (1ull << 63) + (1ull << 62) + (1ull << 61) + 5
61, 83, 113, 151, 211, 281, 379, 509, 683, 911 /  一千以下  
1217, 1627,  2179,  2909,  3881,  6907, 9209,  /一万以下    
12281, 16381, 21841, 29123, 38833, 51787, 69061, 92083/十万以下
122777, 163729, 218357, 291143, 388211, 517619, 690163, 999983/百万以下
1226959, 1635947, 2181271,  2908361,  3877817,  5170427, 6893911,9191891,  /千万以下
12255871, 16341163, 21788233, 29050993, 38734667, 51646229,68861641,  91815541,/一亿以下
1e9+7 和 1e9+9 //十亿左右
122420729,163227661,217636919,290182597,386910137,515880193,687840301,917120411,/十亿以下
1222827239, 1610612741, 3221225473ul, 4294967291ul  
哈希质数表⬆*/

struct Hash_table {
    const ll mod[2] = {998244353, 1000000007};
    const ll seeds[2] = {233, 1331};
    ll h[2][N]{}, P[2][N]{}, _n{};

    void insert(const string &str) {
        _n = str.length();
        P[0][0] = P[1][0] = 1;
        for (int i = 1; i <= _n; i++) {
            P[0][i] = P[0][i - 1] * seeds[0] % mod[0];
            P[1][i] = P[1][i - 1] * seeds[1] % mod[1];
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < _n; j++) {
                h[i][j + 1] = (h[i][j] * seeds[i] % mod[i] + str[j]) % mod[i];
            }
        }
    }

    //将双哈希映射到一个ll值中，如果要进行拼接hash需要修改成返回pair
    ll getHash(int l, int r) 
    {
        ll res[2] = {0};
        res[0] = (h[0][r] - h[0][l - 1] * P[0][r - l + 1] % mod[0] + mod[0]) % mod[0];
        res[1] = (h[1][r] - h[1][l - 1] * P[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
        return res[1] << 30 | res[0];
    }

    //求反向hash值，即从字符串尾部开始hash
    ll revHash(int l, int r) {
        l = _n - l + 1, r = _n - r + 1;
        swap(l, r);
        return getHash(l, r);
    }
} ha;

//二维哈希
char Test[1005][1005], part[1005][1005];
ull B1 = 9973, B2 = 100000007, has[1005][1005], tmp[1005][1005];
int p, q;

void get_hash(char a[1005][1005], int n, int m) {
    ull t1 = 1;
    for (int j = 0; j < q; j++)t1 *= B1;
    for (int i = 0; i < n; i++) {
        ull e = 0;
        for (int j = 0; j < q; j++)e = e * B1 + a[i][j];
        for (int j = 0; j + q <= m; j++) {
            tmp[i][j] = e;
            if (j + q < m)e = e * B1 - t1 * a[i][j] + a[i][j + q];
        }
    }

    ull t2 = 1;
    for (int i = 0; i < p; i++)t2 *= B2;
    for (int j = 0; j + q <= m; j++) {
        ull e = 0;
        for (int i = 0; i < p; i++)e = e * B2 + tmp[i][j];
        for (int i = 0; i + p <= n; i++) {
            has[i][j] = e;
            if (i + p < n)e = e * B2 - t2 * tmp[i][j] + tmp[i + p][j];
        }
    }
}

