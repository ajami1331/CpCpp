#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include "library/EdmondsKarp.h"

namespace solution
{
using namespace std;

const int sz = 2e5 + 10;
const int INF = 1e9 + 10;

int from[555], to[555];
double cap[555];

void Solve()
{
    int n, m;
    int x;

    cin >> n >> m >> x;

    library::EdmondsKarp<INF> flow_graph(n);

    for (int i = 0; i < m; i++)
    {
        cin >> from[i] >> to[i] >> cap[i];
        --from[i];
        --to[i];
    }

    double lo = 1.0 / x, hi = INF, mid;
    int flow;

    for (int iter = 0; iter < 128; iter++)
    {
        mid = (lo + hi) / 2;
        for (int j = 0; j < m; j++)
            flow_graph.SetEdgeCapacity(from[j], to[j], cap[j] / mid, 0);
        flow = flow_graph.MaxFlow(0, n - 1);
        if (flow >= x)
            lo = mid;
        else
            hi = mid;
    }

    cout << fixed << setprecision(10) << (mid)*x << "\n";

    cerr << "-----\n";
}
} // namespace solution
#endif