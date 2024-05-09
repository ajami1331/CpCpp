#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#ifndef solution_h
#define solution_h 1

#include "../library/LCA.h"

namespace solution
{
using namespace std;
const int sz = 2e5 + 10;
const int INF = 1e9 + 10;
void Solve()
{
    int n, q;
    scanf("%d %d", &n, &q);
    library::LCA lca(n);
    for (int i = 1; i < n; i++)
    {
        int v;
        scanf("%d", &v);
        lca.AddEdge(i, v);
    }
    lca.Build(0);
    while (q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", lca.Query(u, v));
    }
}
} // namespace solution
#endif

int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}