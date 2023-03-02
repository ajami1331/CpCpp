#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
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
namespace solution
{
using namespace std;
const int sz = 3e5 + 10;
using ll = long long;
int t, n, k, cs;
library::DisjointSet<sz> ds;
map <int, string> mp1, mp2;
int mask1[sz], mask2[sz];
string a, b;
void Solve()
{
    scanf("%d", &t);
    for (cs = 1; cs <= t; cs++)
    {
        scanf("%d %d", &n, &k);
        ds.Resize(n);
        ds.Reset();
        mp1.clear();
        mp2.clear();
        fill(mask1, mask1 + n, 0);
        fill(mask2, mask2 + n, 0);
        cin >> a >> b;
        for (int i = 0; i < n; i++)
        {
            if (i + k < n)
            {
                ds.MergeSet(i, i + k);
            }
            if (i + k + 1 < n)
            {
                ds.MergeSet(i, i + k + 1);
            }
        }
        for (int i = 0; i < n; i++)
        {
            mp1[ds.FindSet(i)].push_back(a[i]);
            mp2[ds.FindSet(i)].push_back(b[i]);
            mask1[ds.FindSet(i)] ^= (1 << (a[i] - 'a'));
            mask2[ds.FindSet(i)] ^= (1 << (b[i] - 'a'));
        }
        bool fl = true;
        for (int x: ds.GetComponents())
        {
            sort(mp1[x].begin(), mp1[x].end());
            sort(mp2[x].begin(), mp2[x].end());
            if (mask1[x] != mask2[x])
            {
                fl = false;
                break;
            }
        }
        puts(fl ? "YES" : "NO");
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
