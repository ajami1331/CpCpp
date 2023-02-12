#include <algorithm>
#include <iostream>
#include <queue>
#ifndef DisjointSet_h
#define DisjointSet_h 1
namespace library
{
template <int sz> struct DisjointSet
{
    int n;
    int par[sz];
    int cnt[sz];
    int rnk[sz];
    DisjointSet()
    {
    }
    DisjointSet(int n) : n(n)
    {
        this->Reset();
    }
    ~DisjointSet()
    {
    }
    void Resize(int n)
    {
        this->n = n;
        this->Reset();
    }
    void Reset()
    {
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
            cnt[i] = 1;
            rnk[i] = 0;
        }
    }
    int FindParent(int u)
    {
        if (par[u] == u)
        {
            return u;
        }
        return par[u] = FindParent(par[u]);
    }
    bool IsSameSet(int u, int v)
    {
        return FindParent(u) == FindParent(v);
    }
    void MergeSet(int u, int v)
    {
        if (IsSameSet(u, v))
        {
            return;
        }
        u = FindParent(u);
        v = FindParent(v);
        if (cnt[u] < cnt[v])
        {
            std::swap(u, v);
        }
        par[u] = par[v];
        cnt[v] += cnt[u];
    }
};
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
const int sz = 2e5 + 10;
library::DisjointSet<sz> dsu;
void Solve()
{
    int n, q;
    cin >> n >> q;
    dsu.Resize(n);
    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (!t) {
            dsu.MergeSet(a, b);
        } else {
            cout << dsu.IsSameSet(a, b) << "\n";
        }
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
