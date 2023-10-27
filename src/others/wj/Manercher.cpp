char str[N];
int p[N];
void man()// 求解回文串的个数, 最长回文串的长度, 配合hash可以解决大部分回文串问题
{
    int len = strlen(str);
    for(int i = len; i >= 0; i--)
    {
        str[i * 2 + 2] = str[i];
        str[i * 2 + 1] = '#';
    }

    str[0] = '$';

    int mx = 0, id = 0, res = 0;
    for(int i = 0;i <= 2 * len + 1; i++)
    {
        if(i < mx)
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1;
        while (str[i-p[i]] == str[i+p[i]])p[i]++;
        if(i + p[i] > mx)
        {
            id = i;
            mx = p[id] + i;
            res = max(res, p[id] - 1);
        }
    }
}
