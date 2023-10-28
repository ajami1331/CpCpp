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
#include "library/LCA.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
int n, m;
vector<int> g[sz];
library::LCA lca;

void Solve()
{
    scanf("%d %d", &n, &m);
    lca.Init(n);
    for (int i = 2; i <= n; i++)
    {
        int x, y;
        scanf("%d", &x);
        lca.AddEdge(x, i);
    }
    
    lca.Build(1);
    while (m--)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", lca.Query(x, y));
    }
}

} // namespace solution

#endif