// 最长回文子序列
// dp[i][j]表示小标从i开始到j结束的字符串中回文子序列的最大长度为dp[i][j]。
int longestPalindromeSubseq(String s)
{
	int l = s.length();
	int dp[][] = new int[l][l];
	for (int i = l - 1; i >= 0; i--)
	{
		dp[i][i] = 1;
		for (int j = i + 1; j < l; j++)
		{
			if (s.charAt(i) == s.charAt(j))
			{
				if (i + 1 <= j)
					dp[i][j] = dp[i + 1][j - 1] + 2;
			}
			else
				dp[i][j] = Math.max(dp[i + 1][j], Math.max(dp[i][j], dp[i][j - 1]));
		}
	}
	return dp[0][l - 1];
}