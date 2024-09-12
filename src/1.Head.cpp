#pragma GCC optimize(3)
#include <bits/stdc++.h>

#define f(i, n, m) for (long long i = n; i <= m; ++i)
#define unf(i, n, m) for (long long i = n; i >= m; --i)
#define kong NULL
#define debug cout << "sss" << endl;

using ll = long long;
using ull = unsigned long long;
using point_t = double; // 计算几何的默认类型

const double e = exp(1.0);
const double pi = acos(-1.0);
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr ll maxx = 0x3f3f3f3f3f3f3f3f;
constexpr ll minn = 0xc0c0c0c0c0c0c0c0;

#define endl '\n'
constexpr char blank = ' ';
constexpr ll mod = (ll)998244353;
constexpr size_t N = (size_t)1e6 + 6;

#ifdef _DEBUG
#define Crash(...) (__debugbreak(), 0)
#define Debug(...) (__debugbreak(), 0)
#else
#define Crash(...) (exit(-1), 0)
#define Debug(...) ((void)0)
#endif // _DEBUG

#define ensure(expression) (void)(!!(expression) || Crash())

inline void setaccuracy(const std::streamsize &accuracy) {
	std::cout << std::fixed << std::setprecision(accuracy);
}

#define int long long
using namespace std;

void solve() {
	std::cout<< minn<<endl;
}

signed main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int T = 1;
	cin >> T;
	// scanf(" %d", &T);
	// std::cin >> T;
	// for (int q = 1; q <= T; q++) {
	while (T--) {
		solve();
	}

	return 0;
}
