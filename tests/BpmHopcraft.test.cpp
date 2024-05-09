#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#ifndef solution_h
#define solution_h 1

#include "../library/BpmHopcraft.h"

namespace solution
{
using namespace std;
const int sz = 1e5 + 10;
library::BpmHopcraft<sz, sz, sz + sz> bpm;
void Solve()
{
    int l, r, m;
    scanf("%d%d%d", &l, &r, &m);
    bpm.Init(l, r);
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        bpm.AddEdge(u, v);
    }
    printf("%d\n", bpm.MaxMatching());
    for (auto [x, y] : bpm.GetMatching())
    {
        printf("%d %d\n", x, y);
    }
}
} // namespace solution
#endif

int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}