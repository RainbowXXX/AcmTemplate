// luogu-judger-enable-o2
#define _CRT_SECURE_NO_WARNINGS
#pragma GCC optimize(3)
#include <map>
#include <set>
#include <ctime>
#include <regex>
#include <queue>
#include <stack>
#include <random>
#include <math.h>
#include <vector>
#include <string>
#include <time.h>
#include <bitset>
#include <chrono>
#include <memory>
#include <iomanip>
#include <numeric>
#include <complex>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

/*<ignore>
 * test
 </ignore>*/

using ll = long long;
using ull = unsigned long long;
const double e = exp(1.0);
const double pi = acos(-1.0);
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

//constexpr int g = 3;
constexpr char endl = '\n';
constexpr char blank = ' ';
constexpr long double eps = 1e-9;
constexpr double negeps = -eps;
constexpr ll mod = (ll)998244353;
constexpr size_t N = (size_t)1e6 + 6;
constexpr double realinf = std::numeric_limits<double>::infinity();

#define MYCALL
#ifdef _WIN32
#define Crash(...) (__debugbreak(),0)
#define Debug(...) (__debugbreak(),0)
#else
#define Crash(...) (exit(-1),0)
#define Debug(...) ((void)0)
#endif // WIN32

#define ensure(expression) (void)(!!(expression)||Crash())
#define static_ensure(expression) static_assert(expression)