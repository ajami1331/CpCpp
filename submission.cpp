#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#ifndef solution_h
#define solution_h 1
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
    int t, n, root;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &root);
        for (int i = 1; i <= n; i++)
        {
            G[i].clear();
            d[i] = n + 10;
        }
        for (int i = 1; i < n; i++)
        {
            scanf("%d", &c[i]);
        }
        for (int i = 1; i < n; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            G[x].emplace_back(y);
            G[y].emplace_back(x);
        }
        ans = n + 10;
        dfs(root);
        for (int i = 1; i < n; i++)
        {
            dfs(c[i]);
            printf("%d ", ans);
        }
        printf("\n");
    }
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
