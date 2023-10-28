#ifndef DEBUG_H
#define DEBUG_H 1
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#ifndef CLown1331
#define debug(...) 0
#define ASSERT(...) 0
#define dbg(...) 0
#endif
#endif // DEBUG_H
#ifndef DisjointSet_h
#define DisjointSet_h 1
#include <algorithm>
#include <vector>
namespace library
{
template <int sz> struct DisjointSet
{
    int n;
    int par[sz];
    int cnt[sz];
    int rnk[sz];
    int components;
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
        components = n;
    }
    int FindSet(int u)
    {
        if (par[u] == u)
        {
            return u;
        }
        return par[u] = FindSet(par[u]);
    }
    bool IsSameSet(int u, int v)
    {
        return FindSet(u) == FindSet(v);
    }
    void MergeSet(int u, int v)
    {
        if (IsSameSet(u, v))
        {
            return;
        }
        u = FindSet(u);
        v = FindSet(v);
        if (cnt[u] < cnt[v])
        {
            std::swap(u, v);
        }
        par[u] = par[v];
        cnt[v] += cnt[u];
        components--;
    }
    std::vector<int> GetComponents()
    {
        std::vector<int> ret;
        for (int i = 0; i < n; i++)
        {
            if (FindSet(i) == i)
            {
                ret.emplace_back(i);
            }
        }
        return ret;
    }
};
} // namespace library
#endif
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
namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int sz = 2e5 + 105;
int n, m;
int t;
ll ar[sz];
ll c;
library::DisjointSet<sz> ds;
void Solve()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %lld", &n, &c);
        ds.Resize(n);
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &ar[i]);
        }
        bool ok = true;
        vector<int> other;
        for (ll i = 0, j = 1; j < n; j++)
        {
            ll h = c * (i + 1) * (j + 1);
            if (ar[i] + ar[j] >= h)
            {
                ar[i] += ar[j];
                ds.MergeSet(i, j);
                if (other.size())
                {
                    for (int v : other)
                    {
                        ds.MergeSet(i, v);
                        ar[i] += ar[v];
                    }
                    other.clear();
                }
            }
            else
            {
                other.emplace_back(j);
            }
        }
        ok = ds.components == 1;
        if (ok)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
}
} // namespace solution
#endif // solution_h
#define _CRT_SECURE_NO_WARNINGS
int main()
{
    solution::Solve();
    return 0;
}
