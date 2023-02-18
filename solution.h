#ifndef solution_h
#define solution_h 1

#include <cstdio>
#include <cstring>
#include <iostream>
#include "library/BpmHopcraft.h"

namespace solution
{
using namespace std;
const int sz = 1005;
library::BpmHopcraft bpm;
void Solve()
{
    int t, n, m;
    scanf("%d", &t);

    for (int cs = 1; cs <= t; cs++)
    {

        scanf("%d %d", &n, &m);

        bpm.Init(n, n);

        while (m--)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            --x, --y;
            bpm.AddEdge(x, y);
            bpm.AddEdge(y, x);
        }

        printf("Case %d: %d\n", cs, n - (bpm.MaxMatching() / 2));
    }
}
} // namespace solution
#endif