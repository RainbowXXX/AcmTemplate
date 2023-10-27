vector<int> prefix(string s)//求pi数组，即0~i的最长公共前后缀
{
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 and s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
vector<int> find(string text, string pattern)// 求模式串在给定串中出现的位置
{
    string cur = pattern + '#' + text;
    int sz1 = text.size(), sz2 = pattern.size();
    vector<int> v;
    vector<int> lps = prefix(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++)
    {
        if (lps[i] == sz2)
            v.push_back(i - 2 * sz2);
    }
    return v;
}
