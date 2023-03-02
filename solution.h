#ifndef solution_h
#define solution_h 1

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include "library/DisjointSet.h"

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