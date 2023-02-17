#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
#ifndef SparseTable_h
#define SparseTable_h 1
namespace library
{
#define LOG2(x) (32 - __builtin_clz(x) - 1)
template <typename T> struct SparseTable
{
    int n;
    int log2n;
    std::function<T(T, T)> combine;
    std::vector<T> table[32];
    SparseTable()
    {
    }
    SparseTable(const std::vector<T> &arr, std::function<T(T, T)> combine) : SparseTable(arr)
    {
        this->combine = combine;
    }
    SparseTable(const std::vector<T> &arr)
    {
        n = arr.size();
        log2n = LOG2(n) + 1;
        table[0] = arr;
        for (int i = 1; i < log2n; ++i)
        {
            table[i].resize(n - (1 << i) + 1);
            for (int j = 0; j + (1 << i) <= n; j++)
            {
                int x = table[i - 1][j];
                int y = table[i - 1][j + (1 << (i - 1))];
                table[i][j] = Combine(x, y);
            }
        }
    }
    T Combine(T x, T y)
    {
        if (this->combine != nullptr)
            return this->combine(x, y);
        return std::min(x, y);
    }
    T Query(int l, int r)
    {
        int k = LOG2(r - l + 1);
        int x = table[k][l];
        int y = table[k][r - (1 << k) + 1];
        return Combine(x, y);
    }
};
} // namespace library
#endif
#ifndef LCA_H
#define LCA_H 1
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
    LCA(int n) : n(n), log2n(LOG2(2 * n - 1) + 1), graph(n, std::vector<int>()), level(n), parent(n), position(n, -1)
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
        int l = position[u];
        int r = position[v];
        if (l > r)
            std::swap(l, r);
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
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
const int sz = 2e5 + 10;
const int INF = 1e9 + 10;
void Solve()
{
    int n, q;
    scanf("%d %d", &n, &q);
    library::LCA lca(n);
    for (int i = 1; i < n; i++)
    {
        int v;
        scanf("%d", &v);
        lca.AddEdge(i, v);
    }
    lca.Build(0);
    while (q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", lca.Query(u, v));
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
