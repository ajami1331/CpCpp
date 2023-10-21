#ifndef solution_h
#define solution_h 1

#include <algorithm>
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
#include "library/FenwickTree.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
int t, n, m;
char s[sz];
int type, l, r, x;

struct mod_plus : public binary_function<int, int, int>
{
    int operator()(const int &x, const int &y) const
    {
        return (x + y) % 26;
    }
};

struct mod_minus : public binary_function<int, int, int>
{
    int operator()(const int &x, const int &y) const
    {
        return (x - y + 26) % 26;
    }
};

library::FenwickTree<int, sz, mod_plus, mod_minus> ft;

set <int> two, three;

void push(int l, int r)
{
    l = max(l, 1);
    r = min(r, n);
    for (int i = l; i <= r; ++i)
    {
        if (i + 1 <= n && ft.Query(i) == ft.Query(i + 1))
        {
            two.insert(i);
        }
        else 
        {
            two.erase(i);
        }
        if (i + 2 <= n && ft.Query(i) == ft.Query(i + 2))
        {
            three.insert(i);
        }
        else
        {
            three.erase(i);
        }
    }
}

void print()
{
    for (int i = 1; i <= n; ++i)
    {
        printf("%c", ft.Query(i) + 'a');
    }
    printf("\n");
}

void Solve()
{
    scanf("%d", &t);
    while (t-- && scanf("%d %d", &n, &m) == 2)
    {
        s[0] = 0;
        scanf("%s", s + 1);
        ft.Reset();
        two.clear();
        three.clear();
        for (int i = 1; i <= n; ++i)
        {
            ft.Update(i, s[i] - s[i - 1] + 26);
            if (i + 1 <= n && s[i] == s[i + 1])
            {
                two.insert(i);
            }
            if (i + 2 <= n && s[i] == s[i + 2])
            {
                three.insert(i);
            }
        }
        while (m--)
        {
            // print();
            scanf("%d", &type);
            
            if (type == 1)
            {
                scanf("%d %d %d", &l, &r, &x);
                x %= 26;
                ft.RangeUpdate(l, r, x);
                push(l - 5, l + 5);
                push(r - 5, r + 5);
            }
            else
            {
                scanf("%d %d", &l, &r);
                int ans = 0;
                auto it = two.lower_bound(l);
                if (it != two.end() && *it + 1 <= r)
                {
                    ans = 1;
                }
                else
                {
                    it = three.lower_bound(l);
                    if (it != three.end() && *it + 2 <= r)
                    {
                        ans = 1;
                    }
                }
                if (ans > 0)
                {
                    printf("NO\n");
                }
                else
                {
                    printf("YES\n");
                }
            }
        }
    }
}

} // namespace solution

#endif