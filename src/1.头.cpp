#define _CRT_SECURE_NO_WARNINGS
#pragma GCC optimize(3)
#include <map>
#include <set>
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
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1.0);
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

constexpr int g = 3;
constexpr char endl = '\n';
constexpr char blank = ' ';
constexpr double eps = 1e-9;
constexpr double negeps = -eps;
constexpr ll mod = (ll)998244353;
constexpr size_t N = (size_t)2e5 + 5;
constexpr ull realinf = 0x7ff0000000000000;

//代码兼容
#define MYCALL
#ifdef _WIN32
#define Crash() __debugbreak()
#define Debug() __debugbreak()
#else
#define Crash() exit(-1)
#define Debug()
#endif // WIN32

#define ensure(expression) if(!(expression)) Crash();
#define static_ensure(expression) static_assert(expression)