#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#ifndef solution_h
#define solution_h 1

#include "../../library/PersistentSegmentTree.h"

namespace solution
{
using namespace std;
const int sz = 5e5 + 10;
using ll = long long;

library::PersistentSegmentTree<ll, sz> pst;
int n, q;
ll ar[sz];

void Solve()
{
    cin >> n >> q;
    pst.Reset();
    for (int i = 0; i < n; i++)
    {
        cin >> ar[i];
    }

    pst.Build(0, n - 1, ar);

    while (q--)
    {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 0)
        {
            pst.Update(pst.roots.back(), 0, n - 1, x, y);
        }
        else
        {
            cout << pst.Query(pst.roots.back(), 0, n - 1, x, y - 1) << "\n";
        }
    }
}
} // namespace solution
#endif

int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}