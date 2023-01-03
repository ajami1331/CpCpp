#ifndef DisjointSet_h
#define DisjointSet_h 1

#include <algorithm>

namespace library
{
struct DisjointSet
{
    int n;
    int *par;
    int *cnt;
    int *rnk;

    DisjointSet(int n) : n(n)
    {
        par = new int[n];
        cnt = new int[n];
        rnk = new int[n];
        Reset();
    }

    ~DisjointSet()
    {
        delete[] par;
        delete[] cnt;
        delete[] rnk;
    }

    void Reset()
    {
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
            cnt[i] = 1;
            rnk[i] = 0;
        }
    }

    int FindParent(int u)
    {
        if (par[u] == u)
        {
            return u;
        }

        return par[u] = FindParent(par[u]);
    }

    bool IsSameSet(int u, int v)
    {
        return FindParent(u) == FindParent(v);
    }

    void MergeSet(int u, int v)
    {
        if (IsSameSet(u, v))
        {
            return;
        }

        u = FindParent(u);
        v = FindParent(v);
        if (cnt[u] < cnt[v])
        {
            std::swap(u, v);
        }

        par[u] = par[v];
        cnt[v] += cnt[u];
    }
};
} // namespace library
#endif