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
#include "library/Debug.h"
#include "library/DisjointSet.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
int n, m;
int t;
ll ar[sz];
ll c;
library::DisjointSet<sz> ds;

void Solve()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %lld", &n, &c);
        ds.Resize(n);
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &ar[i]);
        }

        bool ok = true;

        vector<int> other;

        for (ll i = 0, j = 1; j < n; j++)
        {
            ll h = c * (i + 1) * (j + 1);
            if (ar[i] + ar[j] >= h)
            {
                ar[i] += ar[j];
                ds.MergeSet(i, j);
                if (other.size())
                {
                    for (int v : other)
                    {
                        ds.MergeSet(i, v);
                        ar[i] += ar[v];
                    }
                    other.clear();
                }
            }
            else
            {
                other.emplace_back(j);
            }
        }

        ok = ds.components == 1;

        if (ok)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
}

} // namespace solution

#endif // solution_h
