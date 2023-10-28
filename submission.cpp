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
#ifndef LCA_H
#define LCA_H 1
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
namespace library
{
constexpr int LOG2(int x)
{
    return 32 - __builtin_clz(x) - 1;
}
template <int sz = 3'00'105, int LG = LOG2(sz)> struct LCA
{
    int n;
    int log2n;
    std::vector<int> graph[sz];
    std::array<int, sz> level;
    std::array<int, sz> parent[LG];
    std::array<int, sz> tr;
    LCA()
    {
    }
    LCA(int n)
    {
        Init(n);
    }
    ~LCA()
    {
    }
    void Init(int n)
    {
        assert(n < sz);
        this->n = n;
        log2n = LOG2(n) + 1;
        for (int i = 0; i <= n; ++i)
        {
            graph[i].clear();
        }
    }
    void AddEdge(int from, int to)
    {
        graph[from].emplace_back(to);
        graph[to].emplace_back(from);
    }
    void Build(int root)
    {
        level[root] = 0;
        parent[0].fill(-1);
        Dfs(root, -1);
    }
    void Dfs(int u, int prev = -1)
    {
        parent[0][u] = prev;
        level[u] = level[prev] + 1;
        tr[u] = 1;
        for (int i = 1; i < log2n; i++)
        {
            parent[i][u] = parent[i - 1][parent[i - 1][u]];
        }
        for (int v : graph[u])
        {
            if (v != prev)
            {
                Dfs(v, u);
                tr[u] += tr[v];
            }
        }
    }
    int Query(int u, int v)
    {
        if (level[u] < level[v])
        {
            std::swap(u, v);
        }
        for (int i = log2n - 1; i >= 0; i--)
        {
            if (level[u] - (1 << i) >= level[v])
            {
                u = parent[i][u];
            }
        }
        if (u == v)
        {
            return u;
        }
        for (int i = log2n - 1; i >= 0; i--)
        {
            if (parent[i][u] != parent[i][v])
            {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        return parent[0][u];
    }
    int Distance(int u, int v)
    {
        int lca = Query(u, v);
        return level[u] + level[v] - 2 * level[lca];
    }
    int KthAncestor(int u, int k)
    {
        assert(k >= 0);
        for (int i = 0; i < log2n; i++)
        {
            if (u == -1)
            {
                break;
            }
            if (k & (1 << i))
            {
                u = parent[i][u];
            }
        }
        return u;
    }
    int KthAncestor(int u, int v, int k)
    {
        int lca = Query(u, v);
        int d = level[u] + level[v] - 2 * level[lca];
        if (k <= level[u] - level[lca])
        {
            return KthAncestor(u, k);
        }
        else
        {
            return KthAncestor(v, d - k);
        }
    }
};
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
#include <algorithm>
#include <climits>
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
namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int sz = 2e5 + 105;
int n, m;
vector<int> g[sz];
library::LCA lca;
void Solve()
{
    scanf("%d %d", &n, &m);
    lca.Init(n);
    for (int i = 2; i <= n; i++)
    {
        int x, y;
        scanf("%d", &x);
        lca.AddEdge(x, i);
    }
    lca.Build(1);
    debug(lca.Query(4, 5));
    dbg(lca.Query(4, 5));
    debug(lca.level);
    while (m--)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", lca.Query(x, y));
    }
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main()
{
    solution::Solve();
    return 0;
}
