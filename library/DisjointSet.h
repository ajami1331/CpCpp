#ifndef DisjointSet_h
#define DisjointSet_h 1

#include <algorithm>
#include <vector>

namespace library
{
template <int sz> struct DisjointSet
{
    int n;
    int par[sz];
    int cnt[sz];
    int rnk[sz];
    int components;

    DisjointSet()
    {
    }

    DisjointSet(int n) : n(n)
    {
        this->Reset();
    }

    ~DisjointSet()
    {
    }

    void Resize(int n)
    {
        this->n = n;
        this->Reset();
    }

    void Reset()
    {
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
            cnt[i] = 1;
            rnk[i] = 0;
        }

        components = n;
    }

    int FindSet(int u)
    {
        if (par[u] == u)
        {
            return u;
        }

        return par[u] = FindSet(par[u]);
    }

    bool IsSameSet(int u, int v)
    {
        return FindSet(u) == FindSet(v);
    }

    void MergeSet(int u, int v)
    {
        if (IsSameSet(u, v))
        {
            return;
        }

        u = FindSet(u);
        v = FindSet(v);
        if (cnt[u] < cnt[v])
        {
            std::swap(u, v);
        }

        par[u] = par[v];
        cnt[v] += cnt[u];

        components--;
    }

    std::vector<int> GetComponents()
    {
        std::vector<int> ret;
        for (int i = 0; i < n; i++)
        {
            if (FindSet(i) == i)
            {
                ret.emplace_back(i);
            }
        }

        return ret;
    }
};
} // namespace library
#endif