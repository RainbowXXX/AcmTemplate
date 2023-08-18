struct Hash {   //三哈希模板
    vector<ll> p1, h1;
    vector<ll> p2, h2;
    vector<ll> p3, h3;
    static const ll M1 = 1e9 + 7, w1 = 131, M2 = 998244353, w2 = 91, M3 = 9999971, w3 = 103;
    //当前的w一定要大于字符集的个数！！
    //w1 = 131, w2 = 13331
    inline void build(string s) {
        h1.clear();
        h2.clear();
        h3.clear();
        h1.emplace_back(0);
        h2.emplace_back(0);
        h3.emplace_back(0);
        p1.emplace_back(1);
        p2.emplace_back(1);
        p3.emplace_back(1);
        int len = s.length();   //注意使用时要将字符串转为下标从一开始的 比如s = '?' + s
        for (int i = 1; i <= len; ++i) {
            h1.emplace_back((h1.back() * w1 % M1 + s[i] - 'a' + 1) % M1);
            h2.emplace_back((h2.back() * w2 % M2 + s[i] - 'a' + 1) % M2);
            h3.emplace_back((h3.back() * w3 % M3 + s[i] - 'a' + 1) % M3);
            p1.emplace_back(p1.back() * w1 % M1);
            p2.emplace_back(p2.back() * w2 % M2);
            p3.emplace_back(p3.back() * w3 % M3);
        }
    }

    tuple<ll, ll, ll> hashval(ll l, ll r) {
        ll res1 = (h1[r] - h1[l - 1] * p1[r - l + 1] % M1) % M1;
        ll res2 = (h2[r] - h2[l - 1] * p2[r - l + 1] % M2) % M2;
        ll res3 = (h3[r] - h3[l - 1] * p3[r - l + 1] % M3) % M3;
        return {(res1 + M1) % M1, (res2 + M2) % M2, (res3 + M3) % M3};
    }
    inline int gethash (int id, int l, int r) {
        if (id == 1) {
            return (h1[r] - h1[l - 1] * p1[r - l + 1] % M1 + M1) % M1;
        } else if (id == 2) {
            return (h2[r] - h2[l - 1] * p2[r - l + 1] % M2 + M2) % M2;
        } else if (id == 3) {
            return (h3[r] - h3[l - 1] * p3[r - l + 1] % M3 + M3) % M3;
        }
        return 0;
    } 
};