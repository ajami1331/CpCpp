#include <cstdio>
#include <iostream>
#include <algorithm>
#ifndef DisjointSet_h
#define DisjointSet_h 1


namespace library
{
    struct DisjointSet {
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
#ifndef solution_h
#define solution_h 1


namespace solution
{
    void Solve()
    {
        int n, ans = 0;
        while (std::cin >> n)
        {
            ans = 0;
            library::DisjointSet dsu(n);
            for (int i = 0; i < n; i++)
            {
                int v;
                std::cin >> v;
                dsu.MergeSet(i, v - 1);
            }
            for (int i = 0; i < n; i++)
            {
                ans += (dsu.FindParent(i) == i);
            }
            std::cout << ans << "\n";
        }
    }
}
#endif
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char* argv[])
{
#ifdef CLown1331
    const clock_t tStart = clock();
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    solution::Solve();
#ifdef CLown1331
    fprintf(stderr, "\n>> Runtime: %.10fs\n", static_cast<double>(clock() - tStart) / CLOCKS_PER_SEC);
    utils::CreateFileForSubmission();
#endif
    return 0;
}
