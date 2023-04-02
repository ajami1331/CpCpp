#ifndef LCA_H
#define LCA_H 1

#include <algorithm>
#include <functional>
#include <vector>
#include "SparseTable.h"

namespace library
{
#define LOG2(x) (32 - __builtin_clz(x) - 1)
struct LCA
{
    int n;
    int log2n;
    std::vector<std::vector<int>> graph;
    std::vector<int> parent;
    std::vector<int> level;
    std::vector<int> tour;
    std::vector<int> position;
    SparseTable<int> sparse_table;
    LCA(int n)
        : n(n), log2n(LOG2(2 * n - 1) + 1), graph(n, std::vector<int>()), level(n), parent(n), position(n, -1)
    {
    }
    ~LCA()
    {
    }

    void AddEdge(int from, int to)
    {
        graph[from].emplace_back(to);
        graph[to].emplace_back(from);
    }

    void Build(int root)
    {
        level[root] = 0;
        Dfs(root, -1);
        sparse_table = SparseTable<int>(tour, [level = level](int x, int y) { return level[x] < level[y] ? x : y; });
    }

    void Dfs(int u, int prev)
    {
        parent[u] = prev;
        level[u] = level[prev] + 1;
        position[u] = tour.size();
        tour.emplace_back(u);
        for (int v : graph[u])
        {
            if (v != prev)
            {
                Dfs(v, u);
                tour.emplace_back(u);
            }
        }
    }

    int Query(int u, int v)
    {
        auto [l, r] = std::minmax(position[u], position[v]);
        return sparse_table.Query(l, r);
    }

    int Distance(int u, int v)
    {
        int lca = Query(u, v);
        return level[u] + level[v] - 2 * level[lca];
    }

    int KthAncestor(int u, int k)
    {
        for (int i = 0; i < log2n; i++)
        {
            if (k & (1 << i))
            {
                u = parent[u];
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