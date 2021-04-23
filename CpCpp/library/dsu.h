#ifndef dsu_h
#define dsu_h 1
#include <vector>
namespace library
{
    struct DisjointSet {
        int n;
        std::vector<int> par, cnt, rnk;

        DisjointSet( int n ) : n(n), par(n), cnt(n), rnk(n)
        {
            Reset();
        }

        void Reset()
        {
            for(int i=0; i<n; i++)
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
}
#endif
