//拓展KMP，又称Z函数，用于求解字符串中所有的真后缀与整个字符串的LCP
/*当将模式串与给定串通过一个特殊字符（'@', '$'等等）拼接，遍历给定串的z函数值
其中z[i]等于模式串的长度 的次数就是KMP的匹配数，因此得名拓展KMP。
*/
vector<int> ex_kmp(string s)
{
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r and z[i - l] < r - i + 1)
        {
            z[i] = z[i - l];
        }
        else
        {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n and s[z[i]] == s[i + z[i]])
                ++z[i];
        }
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
