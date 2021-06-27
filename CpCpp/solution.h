#ifndef solution_h
#define solution_h 1

#include <iostream>
#include "library/DisjointSet.h"

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
