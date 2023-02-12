#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <iostream>
#include <queue>

namespace solution
{
using namespace std;

const int sz = 2e5 + 10;
int c[sz];
int d[sz];
int ans;
vector<int> G[sz];

void dfs(int u, int dist = 0, int par = -1)
{
    d[u] = dist;
    if (dist >= ans)
    {
        return;
    }

    for (int v : G[u])
    {
        if (v == par)
            continue;
        if (d[v] > dist + 1)
            dfs(v, dist + 1, u);
        else
            ans = min(ans, dist + 1 + d[v]);
    }
}

void Solve()
{
    int a, b;
    cin >> a >> b;
    cout << ((a * b) / 2) << "\n";
}
} // namespace solution
#endif