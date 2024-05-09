#ifndef BpmDfs_h
#define BpmDfs_h 1

#include "Common.h"

namespace library
{

template <size_t sz> struct BpmDfs
{
    int n;
    bool fl[sz];
    int match[sz];
    bool g[sz][sz];

    BpmDfs()
    {
    }

    BpmDfs(int n)
    {
        Init(n);
    }

    ~BpmDfs()
    {
    }

    void Init(int n)
    {
        this->n = n;
    }

    void AddEdge(int u, int v)
    {
        g[u][v] = true;
    }

    void Clear()
    {
        memset(g, 0, sizeof g);
    }

    bool Dfs(int u)
    {
        for (int v = 0; v < n; v++)
        {
            if (g[u][v] && !fl[v])
            {
                fl[v] = true;
                if (match[v] == -1 || Dfs(match[v]))
                {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    int MaxMatching()
    {
        memset(match, -1, sizeof match);
        int ret = 0;
        for (int i = 0; i < n; i++)
        {
            memset(fl, 0, sizeof fl);
            if (Dfs(i))
            {
                ret++;
            }
        }
        return ret;
    }
};

} // namespace library
#endif