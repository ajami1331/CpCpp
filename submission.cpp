#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int sz = 2e5 + 105;
int t, n, m;
vector<pair<int, int>> g[sz];
bool vis[sz];
int color[sz];
bool dfs(int u, int c)
{
    vis[u] = true;
    color[u] = c;
    for (auto &v : g[u])
    {
        if (!vis[v.first])
        {
            dfs(v.first, c + v.second);
        }
        else if (color[v.first] != c + v.second)
        {
            return false;
        }
    }
    return true;
}
void Solve()
{
    scanf("%d", &t);
    while (t-- && scanf("%d %d", &n, &m) == 2)
    {
        for (int i = 0; i <= n; i++)
        {
            g[i].clear();
            vis[i] = false;
            color[i] = 0;
        }
        for (int i = 0; i < m; i++)
        {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, -w);
        }
        bool ok = true;
        for (int i = 1; i <= n && ok; i++)
        {
            if (!vis[i])
            {
                ok = ok && dfs(i, 1);
            }
        }
        for (int i = 1; i <=n && ok ;i++)
        {
            for (auto &v : g[i])
            {
                if (color[v.first] != color[i] + v.second)
                {
                    ok = false;
                    break;
                }
            }
        }
        puts(ok ? "YES" : "NO");
    }
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
