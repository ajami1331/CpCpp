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
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
#include "library/Debug.h"
#include "library/Rerooter.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = long long;
const int sz = 2e5 + 105;
struct Solution
{
    int n;

    void Solve()
    {
        scanf("%d", &n);
        vector<vector<int>> g(n);
        vector<vector<int>> dir(n);
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            --u;
            --v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
            dir[u].emplace_back(0);
            dir[v].emplace_back(1);
        }

        using Aggregate = int;
        using Value = int;

        auto base = [](int) -> Aggregate { return 0; };

        auto merge_into = [&](Aggregate a, Value b, int vertex, int edge_index) -> Aggregate {
            return a + b + dir[vertex][edge_index];
        };

        auto finalize_merge = [](Aggregate a, int vertex, int edge_index) -> Value { return a; };

        auto [reroot, f, r] = library::reroot::rerooter(g, base, merge_into, finalize_merge);

        int ans = *min_element(reroot.begin(), reroot.end());

        printf("%d\n", ans);

        for (int i = 0; i < n; i++)
        {
            if (reroot[i] == ans)
            {
                printf("%d ", i + 1);
            }
        }
    }
};

} // namespace solution

#endif // solution_h
