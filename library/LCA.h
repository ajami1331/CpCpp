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