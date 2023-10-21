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
#include "library/FenwickTreeRangeSum.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
int t, n, m;
char s[sz];
library::FenwickTreeRangeSum<int, sz> ft_two;
library::FenwickTreeRangeSum<int, sz> ft_three;
library::FenwickTreeRangeSum<int, sz> st;
int type, l, r, x;

int query(int x)
{
    return st.QueryPoint(x) % 26;
}
void print()
{
    for (int i = 1; i <= n; ++i)
    {
        cout << (char)(query(i) + 'a');
    }
    cout << endl;
}

void Solve()
{
    scanf("%d", &t);
    while (t-- && scanf("%d %d", &n, &m) == 2)
    {
        scanf("%s", s + 1);
        ft_two.Reset();
        ft_three.Reset();
        st.Reset();
        for (int i = 1; i <= n; ++i)
        {
            st.Update(i, s[i] - 'a');
            if (i + 1 <= n && s[i] == s[i + 1])
            {
                ft_two.RangeUpdate(i, i + 1, 1);
            }
            if (i + 2 <= n && s[i] == s[i + 2])
            {
                ft_three.RangeUpdate(i, i + 2, 1);
            }
        }
        while (m--)
        {
            scanf("%d", &type);
            if (type == 1)
            {
                scanf("%d %d %d", &l, &r, &x);
                x %= 26;
                if (x == 0)
                {
                    continue;
                }
                for (int i = max(1, l - 5); i <= min(l + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, -1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, -1);
                    }
                }
                for (int i = max(1, r - 5); i <= min(r + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, -1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, -1);
                    }
                }
                st.RangeUpdate(l, r, x);
                for (int i = max(1, l - 5); i <= min(l + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, 1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, 1);
                    }
                }
                for (int i = max(1, r - 5); i <= min(r + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, 1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, 1);
                    }
                }
            }
            else
            {
                scanf("%d %d", &l, &r);
                int ans = 0;
                if (l + 1 <= r && !ans)
                {
                    ans += query(l) == query(l + 1);
                }
                if (l <= r - 1 && !ans)
                {
                    ans += query(r - 1) == query(r);
                }
                if (l + 1 <= r - 1 && !ans)
                {
                    ans += ft_two.QueryRange(l + 1, r - 1);
                }
                if (l + 2 <= r && !ans)
                {
                    ans += query(l) == query(l + 2);
                }
                if (l <= r - 2 && !ans)
                {
                    ans += query(r - 2) == query(r);
                }
                if (l + 2 <= r - 2 && !ans)
                {
                    ans += ft_three.QueryRange(l + 2, r - 2);
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