#ifndef COMMON_H
#define COMMON_H 1
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <random>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define szx(x) (int)(x).size()
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
constexpr int LOG2(int x)
{
    return 32 - __builtin_clz(x) - 1;
}
#endif // COMMON_H
#ifndef DEBUG_H
#define DEBUG_H 1
#ifndef CLown1331
#define debug(...) 0
#define ASSERT(...) 0
#define dbg(...) 0
#endif
#endif // DEBUG_H
#ifndef solution_h
#define solution_h 1
namespace solution
{
const int sz = 3e5 + 105;
const int mod = 1e9 + 7;
void solve()
{
    int t, a, b, c;
    cin >> t;
    while (t-- && cin >> a >> b >> c)
    {
        cout << (a ^ b ^ c) << "\n";
    }
}
} // namespace solution
#endif // solution_h
#define _CRT_SECURE_NO_WARNINGS
int main()
{
    solution::solve();
    return 0;
}
