// #define NDEBUG
// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using db = double;
void Main(void);
int main(void)
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#if defined(TEXT_IO) and defined(LOCAL) and not defined(ONLINE_JUDGE)
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	Main();
	return 0;
}
/**************************************************/
namespace my
{
#if defined(LOCAL) and not defined(ONLINE_JUDGE)
#include "D:\VScodeFile\LOCAL\debug.h"
#define DBG(x) std::cerr << "! " #x " = " << (x) << std::endl
#else
#define dbg(...) ((void)0)
#define DBG(...) ((void)0)
#endif
#define VE std::vector
#define STR std::string
#define HEAP std::priority_queue
#define PLL std::pair<ll, ll>
#define fi first
#define se second
#define EDL '\n'
#define WS ' '
#define SDP(x) std::fixed << std::setprecision(x)
#define SZ(x) ((ll)x.size())
#define FOR(i, l, r) for (ll i = (l); i <= (r); ++i)
#define ROF(i, r, l) for (ll i = (r); i >= (l); --i)
	constexpr int inf = 0x3f3f3f3f;
	constexpr long long INF = 0x3f3f3f3f3f3f3f3fLL;
	constexpr db EPS = 1.0e-9;
	constexpr ll MOD2 = 1e9 + 7;
	constexpr ll MOD = 998244353;
	constexpr ll SZ2 = 1e3 + 3;
	constexpr ll SZ = 2e5 + 5;
}
using namespace my;
namespace fastIO
{
	constexpr ll BUF_SZ = 1e5 + 5;
	bool IOrun = true;
	char NC(void)
	{
		static char buf[BUF_SZ], *p = buf + BUF_SZ, *ed = buf + BUF_SZ;
		if (p != ed)
			return *p++;
		p = buf;
		ed = buf + fread(buf, 1, BUF_SZ, stdin);
		if (p == ed)
		{
			IOrun = false;
			return -1;
		}
		return *p++;
	}
	bool BLK(char c) { return c == WS or c == EDL or c == '\r' or c == '\t'; }
	template <class T>
	bool FIN(T &x)
	{
		bool sign = false;
		char c = NC();
		x = 0;
		while (BLK(c))
			c = NC();
		if (not IOrun)
			return false;
		if (c == '-')
		{
			sign = true;
			c = NC();
		}
		while ('0' <= c and c <= '9')
		{
			x = x * 10 + c - '0';
			c = NC();
		}
		if (sign)
			x = -x;
		return true;
	}
	bool FIN(db &x)
	{
		bool sign = false;
		char c = NC();
		x = 0;
		while (BLK(c))
			c = NC();
		if (not IOrun)
			return false;
		if (c == '-')
		{
			sign = true;
			c = NC();
		}
		while ('0' <= c and c <= '9')
		{
			x = x * 10 + c - '0';
			c = NC();
		}
		if (c == '.')
		{
			db w = 1.0;
			c = NC();
			while ('0' <= c and c <= '9')
			{
				w /= 10.0;
				x += w * (c - '0');
				c = NC();
			}
		}
		if (sign)
			x = -x;
		return true;
	}
	bool FIN(char &c)
	{
		c = NC();
		while (BLK(c))
			c = NC();
		if (not IOrun)
		{
			c = -1;
			return false;
		}
		return true;
	}
	bool FIN(char *s)
	{
		char c = NC();
		while (BLK(c))
			c = NC();
		if (not IOrun)
			return false;
		while (IOrun and not BLK(c))
		{
			*s++ = c;
			c = NC();
		}
		*s = 0;
		return true;
	}
	bool LIN(char *s)
	{
		char c = NC();
		while (BLK(c))
			c = NC();
		if (not IOrun)
			return false;
		while (IOrun and c != EDL)
		{
			*s++ = c;
			c = NC();
		}
		*s = 0;
		return true;
	}
	template <class T, class... Y>
	bool FIN(T &x, Y &...o) { return FIN(x) and FIN(o...); }
	void FIN(ll *a, ll l, ll r)
	{
		FOR(i, l, r)
		FIN(a[i]);
		return;
	}
	void FIN(db *a, ll l, ll r)
	{
		FOR(i, l, r)
		FIN(a[i]);
		return;
	}
	void FIN(char *a, ll l, ll r)
	{
		FOR(i, l, r)
		FIN(a[i]);
		return;
	}
}
using fastIO::FIN;
using fastIO::LIN;
/**************************************************/

void Main(void)
{
	
	return;
}