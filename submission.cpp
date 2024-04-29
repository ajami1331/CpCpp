#ifndef DEBUG_H
#define DEBUG_H 1
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#ifndef CLown1331
#define debug(...) 0
#define ASSERT(...) 0
#define dbg(...) 0
#endif
#endif // DEBUG_H
#ifndef solution_h
#define solution_h 1
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
namespace solution
{
using namespace std;
using ll = long long;
using ull = long long;
const int sz = 3e5 + 105;
const int mod = 1e9 + 7;
const ll max_possible = 1LL * sz * mod;
int t, n, k;
ll a[sz], b[sz];
vector<pair<ll, ll>> vp;
void solve()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &a[i]);
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &b[i]);
        }
        vp.clear();
        for (int i = 0; i < n; i++)
        {
            if (a[i] < b[i])
            {
                vp.emplace_back(a[i], b[i]);
            }
        }
        ll ans = 0;
        if (vp.size() < k)
        {
            printf("0\n");
            continue;
        }
        sort(vp.begin(), vp.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
            if (a.first == b.first)
                return a.second > b.second;
            return a.first > b.first;
        });
        ll sum = 0;
        for (int i = 0; i < k; i++)
        {
            sum -= vp[i].first;
        }
        for (int i = k; i < vp.size(); i++)
        {
            sum += (vp[i].second - vp[i].first);
        }
        ans = max(ans, sum);
        for (int i = 0; i + k < vp.size(); i++)
        {
            sum -= vp[i + k].first;
            sum -= (vp[i + k].second - vp[i + k].first);
            sum += vp[i].first;
            ans = max(ans, sum);
        }
        printf("%lld\n", ans);
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
