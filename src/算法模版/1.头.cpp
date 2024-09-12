// luogu-judger-enable-o2
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#pragma GCC optimize(3)
#include <map>
#include <set>
#include <ctime>
#include <regex>
#include <queue>
#include <stack>
#include <random>
#include <cmath>
#include <vector>
#include <string>
#include <ctime>
#include <bitset>
#include <chrono>
#include <memory>
#include <iomanip>
#include <numeric>
#include <complex>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using ll = long long;
using point_t = double; // 计算几何的默认类型
using ull = unsigned long long;
const double e = exp(1.0);
const double pi = acos(-1.0);
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

//constexpr int g = 3;
constexpr char endl = '\n';
constexpr char blank = ' ';
constexpr point_t eps = 1e-9;
constexpr ll mod = (ll)998244353;
constexpr point_t negeps = -eps;
constexpr size_t N = (size_t)1e6 + 6;
constexpr double realinf = std::numeric_limits<double>::infinity();

#define MYCALL
#ifdef _DEBUG
#define Crash(...) (__debugbreak(),0)
#define Debug(...) (__debugbreak(),0)
#else
#define Crash(...) (exit(-1),0)
#define Debug(...) ((void)0)
#endif // _DEBUG

#define ensure(expression) (void)(!!(expression)||Crash())
#define static_ensure(expression) static_assert(expression)