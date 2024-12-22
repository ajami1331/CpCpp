#ifndef COMMON_H
#define COMMON_H 1
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <chrono>
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
const int sz = 2e5 + 105;
const int mod = 1e9 + 7;
const ll INF = 1e16;
bool is_regular(const string& s)
{
    int cnt = 0;
    for (char c: s)
    {
        if (c == '(') cnt++;
        else cnt--;
        if (cnt < 0) return false;
    }
    return cnt == 0;
}
bool is_beautiful(string s)
{
    if (is_regular(s)) return true;
    reverse(all(s));
    return is_regular(s);
}
void solve()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        string s;
        cin >> n >> s;
        if (is_beautiful(s))
        {
            printf("1\n1");
            for (int i = 1; i < n; i++)
            {
                printf(" 1");
            }
            printf("\n");
            continue;
        }
        int cnt = 0;
        vector <int> ans;
        int color = 0;
        for (char c: s)
        {
            if (cnt == 0) color = c == ')';
            if (c == '(') cnt++;
            else cnt--;
            ans.push_back(color);
        }
        string part1, part2;
        for (int i = 0; i < n; i++)
        {
            if (ans[i] == 0) part1.push_back(s[i]);
            else part2.push_back(s[i]);
        }
        if (is_beautiful(part1) && is_beautiful(part2))
        {
            printf("2\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", ans[i] + 1);
            }
            printf("\n");
        }
        else
        {
            printf("-1\n");
        }
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
